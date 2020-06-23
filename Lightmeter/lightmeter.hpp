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
    BH1750 & sensor;
    BH1750_Average avgSensor = BH1750_Average(sensor);
    hwlib::terminal_from & display;
    float lux, ExposureValue, Apperature = 0;
    int shutterSpeed = 0;
    int ISO = 100;

public:
    lightmeter(BH1750 & sensor, hwlib::terminal_from & display);

    float log2(float x);

    float luxToEv();

    void configMeasurement(BH1750::MODE mode);

    float getLux();

    float getISO();

    float getApperature();

    float getShutterspeed();

    // void refresh();

    // void showISOmenu();

    // void showApperatureMenu();

    // void showShutterspeedMenu();

    // void showSettingsMenu();

};

#endif //LIGHTMETER_hpp