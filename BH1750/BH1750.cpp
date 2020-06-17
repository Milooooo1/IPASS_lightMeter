#include "hwlib.hpp"
#include "BH1750.hpp"

BH1750::BH1750(uint8_t address = 0x23, hwlib::target::pin_out addr = hwlib::target::pins::pin_out_dummy):
    address( address),
    addr_pin( addr )
{}

void BH1750::PowerDown(){
    {
		auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   		writetr.write(POWER_DOWN);
	}
}

void BH1750::PowerOn(){
    {
		auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   		writetr.write(POWER_UP);
	}
}

void BH1750::Reset(){
	{
		auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   		writetr.write(RESET);
	}   
}

void BH1750::Configure(MODE mode){
    {
		auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   		writetr.write(mode);
	}
}

uint16_t BH1750::GetLightIntensity(void){
    uint8_t result[2];
    uint16_t LuxValue = 0;
	{
		auto readtr = ((hwlib::i2c_bus*)(&bus))->read(address);
		readtr.read(result, 2);
	}
    return LuxValue / 1.2;
}