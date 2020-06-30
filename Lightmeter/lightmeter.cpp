// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "lightmeter.hpp"

lightmeter::lightmeter(BH1750 & sensor):
    sensor( sensor )
    {}

float lightmeter::log2(float x){
    return log(x) / log(2);
}

float lightmeter:: getEv(){
    return log2(sensor.getLightIntensity() / 2.5);
}

void lightmeter::configMeasurement(BH1750::MODE mode){
    sensor.configure(mode);
}

float lightmeter::getLux(){
    return sensor.getLightIntensity();
}

int lightmeter::getCorrectISO(float x){
    float ISO[19] = { 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 4000, 5000, 6400 };
    float nearest = ISO[18];
    float previousDifference = 10000;
    for(int i = 18; i > 0; i--){
        if(abs(x - ISO[i]) < previousDifference){
            nearest = ISO[i];
            previousDifference = abs(x - ISO[i]);
        }
    }
    return nearest;
}

float lightmeter::getISO(float shutterspeed, float aperture){
    return getCorrectISO((((pow(aperture, 2.0) / shutterspeed) * 12.5) / 2));
}

float lightmeter::getCorrectAperture(float x){
    float aperture[12] = { 1.1, 1.2, 1.4, 1.8, 2.0, 2.8, 4, 5.6, 8, 11, 16, 22 };
    float nearest = aperture[11];
    float previousDifference = 5;
    for(int i = 11; i > 0; i--){
        if(abs(x - aperture[i]) < previousDifference){
            nearest = aperture[i];
            previousDifference = abs(x - aperture[i]);
        }
    }
    return nearest;
}

float lightmeter::getAperture(int ISO, float shutterSpeed){
    return getCorrectAperture(sqrt(((ISO * getEv()) / 12.5 ) * shutterSpeed));
}

int lightmeter::getCorrectShutterspeed(float x){
double shutterspeed[34] = { 0.25, 0.2, 0.167, 0.125, 0.1, 0.077, 0.067, 0.05, 0.04, 0.03, 0.025, 0.02, 0.0167, 0.0125, 0.01, 
                         0.008, 0.00625, 0.005, 0.004, 0.003125, 0.0025, 0.002, 0.0015625, 0.00125, 0.001, 
                         0.0008, 0.000625, 0.0005, 0.0004, 0.0003125, 0.00025, 0.0002, 0.00015625, 0.000125 };
    float previousDifference = 10;
    float nearest = shutterspeed[33];
    for(int i = 33; i > 0; i--){
        if(abs(x - shutterspeed[i]) < previousDifference ){
            nearest = shutterspeed[i];
            previousDifference = abs(x - shutterspeed[i]);
        }
    }
    return ceil(1 / nearest);
}

float lightmeter::getShutterspeed(float aperature, int ISO){
    return getCorrectShutterspeed(pow(aperature, 2)/((ISO * 2) / 12.5));
}

// Standard formula:
// N^2 / t = L * S / K
// N = Aperture
// t = shutterspeed (time)
// L = EV (Luminance)
// S = ISO
// K = constant (12.5)