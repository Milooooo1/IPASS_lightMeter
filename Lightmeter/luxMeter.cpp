#include "hwlib.hpp"
#include "BH1750.hpp"

int main(void){

    hwlib::wait_ms(500);

    auto scl     = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda     = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
  
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from( oled, font );

    auto sensor = BH1750();
    sensor.Configure(sensor.CONTINUOUSLY_H_RES);

    uint16_t previous = 0;
    for(;;){
        uint16_t lux = sensor.GetLightIntensity();
        if(previous != lux){
            display << "\n"
                    <<"Light: " << lux << " Lux" << hwlib::flush;
            hwlib::cout 
                    <<"Light: " << lux << " Lux \n";
        }
        hwlib::wait_ms(400);
        if(lux != sensor.GetLightIntensity()){
            display << "\f" << hwlib::flush;
        } 
        previous = lux;    
    }

}