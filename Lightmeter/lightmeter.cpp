// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "lightmeter.hpp"

lightmeter::lightmeter(BH1750 & sensor, hwlib::terminal_from & display):
    sensor( sensor ),
    display( display )
    {}

float lightmeter::log2(float x){
    return log(x) / log(2);
}

float lightmeter:: luxToEv(){
    return log2(sensor.GetLightIntensity() / 2.5);
}

void lightmeter::configMeasurement(BH1750::MODE mode){
    sensor.Configure(mode);
}

float lightmeter::getLux(){
    return sensor.GetLightIntensity();
}

float lightmeter::getISO(){
    return ((pow(Apperature, 2.0) / shutterSpeed) * 12.5) / ExposureValue; 
}

float lightmeter::getApperature(){
    return sqrt((ISO * ExposureValue) / 12.5) * shutterSpeed;
}

float lightmeter::getShutterspeed(){
    return pow(Apperature, 2)/((ISO * ExposureValue) / 12.5);
}

// void lightmeter::refresh(){

// }

// void lightmeter::showISOmenu(){
//     display << "ISO: \n" << ISO << hwlib::flush;
// }

// void lightmeter::showApperatureMenu();

// void lightmeter::showShutterspeedMenu();

// void lightmeter::showSettingsMenu(){
//     display << "ISO = " << ISO
//             << "\n t = " << shutterSpeed
//             << "\n f/" << Apperature
//             << hwlib::flush;
// }

// N^2 / t = L * S / K
// N = Apperature
// t = shutterspeed (time)
// L = EV (Luminance)
// S = ISO
// K = constant (12.5)
