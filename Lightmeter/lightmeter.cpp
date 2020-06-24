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
    return log2(sensor.GetLightIntensity() / 2.5);
}

void lightmeter::configMeasurement(BH1750::MODE mode){
    sensor.Configure(mode);
}

float lightmeter::getLux(){
    return sensor.GetLightIntensity();
}

unsigned int lightmeter::getISO(float Apperature, int shutterSpeed){
    int tmp = ((pow(Apperature, 2.0) / shutterSpeed) * 12.5) / getEv();
    if(tmp >= 100 && tmp < 125){
        return 100;
    } else if(tmp >= 125 && tmp < 160) {
        return 125;
    } else if(tmp >= 160 && tmp < 200) {
        return 160;
    } else if(tmp >= 200 && tmp < 250) {
        return 200;
    } else if(tmp >= 250 && tmp < 320) {
        return 250;
    } else if(tmp >= 320 && tmp < 400) {
        return 320;
    } else if(tmp >= 400 && tmp < 500) {
        return 400;
    } else if(tmp >= 500 && tmp < 640) {
        return 500;
    } else if(tmp >= 640 && tmp < 800) {
        return 640;
    } else if(tmp >= 800 && tmp < 1000) {
        return 800;
    } else if(tmp >= 1000 && tmp < 1250) {
        return 1000;
    } else if(tmp >= 1250 && tmp < 1600) {
        return 1250;
    } else if(tmp >= 1600 && tmp < 2000) {
        return 1600;
    } else if(tmp >= 2000 && tmp < 2500) {
        return 2000;
    } else if(tmp >= 2500 && tmp < 3200) {
        return 2500;
    } else if(tmp >= 3200 && tmp < 4000) {
        return 3200;
    } else if(tmp >= 4000 && tmp < 5000) {
        return 4000;
    } else if(tmp >= 5000 && tmp < 6400) {
        return 5000;
    } else if(tmp >= 6400 && tmp <= 6400) {
        return 6400;
    } else {
        return tmp;
    } 
}

float lightmeter::getApperature(int ISO, int shutterSpeed){
    float tmp = sqrt(((ISO * getEv()) / 12.5 )* shutterSpeed) ;
    if(tmp >= 1.2 && tmp < 1.4){
        return 1.2;
    } else if(tmp >= 1.4 && tmp < 1.8) {
        return 1.4;
    } else if(tmp >= 1.8 && tmp < 2.0) {
        return 1.8;
    } else if(tmp >= 2.0 && tmp < 2.8) {
        return 2.0;
    } else if(tmp >= 2.8 && tmp < 4.0) {
        return 2.8;
    } else if(tmp >= 4.0 && tmp < 5.6) {
        return 4.0;
    } else if(tmp >= 5.6 && tmp < 8.0) {
        return 5.6;
    } else if(tmp >= 8.0 && tmp < 11) {
        return 8.0;
    } else if(tmp >= 11 && tmp < 16) {
        return 11;
    } else if(tmp >= 16 && tmp <= 22) {
        return 22;
    } else {
        return tmp;
    }
}

unsigned int lightmeter::getShutterspeed(float Apperature, int ISO){
    return pow(Apperature, 2)/((ISO * getEv()) / 12.5);
}


// Standard formula:
// N^2 / t = L * S / K
// N = Apperature
// t = shutterspeed (time)
// L = EV (Luminance)
// S = ISO
// K = constant (12.5)
