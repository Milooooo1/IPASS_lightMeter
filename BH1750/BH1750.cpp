// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

//#include "hwlib.hpp"
#include "BH1750.hpp"

BH1750::BH1750(uint8_t address/*, hwlib::target::pin_out addr*/):
    address( address) //,
    //addr_pin( addr )
{}

void BH1750::PowerDown(){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
    writetr.write(POWER_DOWN);
}

void BH1750::PowerOn(){
    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(POWER_UP);
}

void BH1750::Reset(){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(RESET);  
}

void BH1750::Configure(MODE mode){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(mode);
}

void BH1750::ConfigureMTREG(MTREGT_MODES mode){
    if(mode <= 31 || mode > 254){
        return;
    }
    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write((0b01000 << 3) | (mode >> 5));
    writetr.write((0b011 << 5)   | (mode & 0b11111));
}

uint16_t BH1750::GetLightIntensity(void){
    uint8_t result[2];
    uint16_t LuxValue = 0;
	{
		auto readtr = ((hwlib::i2c_bus*)(&bus))->read(address);
		readtr.read(result, 2);
	}
    LuxValue = result[0] + result[1];
    return LuxValue / 1.2;
}