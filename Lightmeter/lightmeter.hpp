// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef LIGHTMETER_HPP
#define LIGHTMETER_HPP

#include "BH1750.hpp"
#include "BH1750_Average.hpp"
#include "hwlib.hpp"
#include <math.h>

class lightmeter {
private:
    BH1750 sensor = BH1750();
    BH1750_Average avgSensor = BH1750_Average(sensor);
    hwlib::font_default_8x8 font8x8 = hwlib::font_default_8x8();
    hwlib::font_default_16x16 font16x16 = hwlib::font_default_16x16();
    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    hwlib::terminal_from display = hwlib::terminal_from( oled, font8x8 );
    float lux, ExposureValue = 0;
    
public:
    lightmeter();

    float log2(float x);

    float luxToEv();

    void configMeasurement(sensor.MODE mode = CONTINUOUSLY_H_RES);

    float getLux();

    float getISO();

    float getApperature();

    float getShutterspeed();

    void refresh();

    void showISOmenu();

    void showApperatureMenu();

    void showShutterspeedMenu();

    void showMainMenu();

};

#endif //LIGHTMETER_hpp