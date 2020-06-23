#include "hwlib.hpp"
#include "lightmeter.hpp"

int main(void){
    BH1750 sensor = BH1750();
    BH1750_Average avgSensor = BH1750_Average(sensor);

    auto font8x8 = hwlib::font_default_8x8();
    auto font16x16 = hwlib::font_default_16x16();

    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    auto display = hwlib::terminal_from( oled, font8x8 );

    lightmeter meter = lightmeter(sensor, display);
    meter.configMeasurement(sensor.CONTINUOUSLY_H_RES);
    sensor.Configure(sensor.CONTINUOUSLY_H_RES);

    int ExposureValue = 0;
    int Lux = 0;
    for(;;){
        Lux = sensor.GetLightIntensity();
        ExposureValue = meter.luxToEv();
        display << "EV: " << ExposureValue << "\n"
                << "Lux: " << Lux << hwlib::flush;
        hwlib::wait_ms(10);
        display << "\f" << hwlib::flush;
    }
}