// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "BH1750.hpp"

BH1750::BH1750(uint8_t address):
    address( address)
{}

void BH1750::powerDown(){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
    writetr.write(POWER_DOWN);
}

void BH1750::powerOn(){
    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(POWER_UP);
}

void BH1750::reset(){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(RESET);  
}

void BH1750::configure(MODE mode){
	auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write(mode);
}

void BH1750::configureMTREG(MTREGT_MODES mode){
    if(mode <= 31 || mode > 254){
        hwlib::cout << "No valid input.\n";
        return;
    }
    auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   	writetr.write((0b01000 << 3) | (mode >> 5));        //high bit
    writetr.write((0b011 << 5)   | (mode & 0b11111));   //low bit
}

uint16_t BH1750::getLightIntensity(){
    uint8_t result[2];
    uint16_t LuxValue = 0;
	auto readtr = ((hwlib::i2c_bus*)(&bus))->read(address);
	readtr.read(result, 2);
    LuxValue = result[0] + result[1];
    return (uint16_t)(LuxValue / 1.2);
}
