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
    float lux, ExposureValue = 0;

public:
    lightmeter(BH1750 & sensor);

    float log2(float x);

    float getEv();

    void configMeasurement(BH1750::MODE mode);

    float getLux();

    unsigned int getISO(float Apperature, int shutterSpeed);

    float getApperature(int ISO, int shutterSpeed);

    unsigned int getShutterspeed(float Apperature, int ISO);
};

#endif //LIGHTMETER_hpp