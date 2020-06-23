// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "lightmeter.hpp"

lightmeter::lightmeter():
    {}

float lightmeter::log2(float x){
    return log(x) / log(2);
}

float lightmeter:: luxToEv(){
    return log2(lux / 2.5);
}

void lightmeter::configMeasurement(sensor.MODE mode = CONTINUOUSLY_H_RES){
    sensor.Configure(mode);
}

float lightmeter::getLux(){
    return sensor.GetLightIntensity();
}

float lightmeter::getISO();

float lightmeter::getApperature();

float lightmeter::getShutterspeed();

void lightmeter::refresh();

void lightmeter::showISOmenu();

void lightmeter::showApperatureMenu();

void lightmeter::showShutterspeedMenu();

void lightmeter::showMainMenu();

