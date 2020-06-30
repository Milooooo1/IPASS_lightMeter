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

/// @file

/// \brief
/// Lightmeter camera C++ Library
/// \details
/// This is a C++ Library using the BH1750 library 
/// to measure the lightintensity and calculates
/// the Aperture, Shutterspeed or ISO which you
/// can enter into your camera to get a correctly
/// exposed photo. 

class lightmeter {
private:
    BH1750 & sensor;
    BH1750_Average avgSensor = BH1750_Average(sensor);
    float lux, ExposureValue = 0;

public:
    /// \brief
    /// Constructor
    /// \details
    /// The constructor for the lightmeter
    /// needs a sensor to measure the lightintensity
    lightmeter(BH1750 & sensor);

    /// \brief
    /// log2
    /// \details
    /// This function makes it easier and more
    /// readable to use log2
    float log2(float x);

    /// \brief
    /// Get exposure value
    /// \details
    /// This function calls the sensor to measure
    /// the lightintensity and calculates the 
    /// exposure value which is needed to calculate
    /// the shutterspeed, aperture or ISO
    float getEv();

    /// \brief
    /// Configure measurement mode
    /// \details
    /// This function configures in which
    /// mode the sensor measures the lightintensity
    void configMeasurement(BH1750::MODE mode);

    /// \brief
    /// Get exposure value
    /// \details
    /// This function calls the sensor to measure
    /// the lightintensity.
    float getLux();

    /// \brief
    /// Get photography style ISO
    /// \details
    /// This function rounds the exact ISO to
    /// the closest photography-style ISO
    int getCorrectISO(float x);

    /// \brief
    /// Calculate ISO
    /// \details
    /// This function calculates the ISO, it needs
    /// the aperture and shutterspeed which are 
    /// configured by the user. 
    float getISO(float Aperture, float shutterSpeed);

    /// \brief
    /// Get photography style aperture
    /// \details
    /// This function rounds the exact aperature to
    /// the closest photography-style aperature
    float getCorrectAperture(float x);

    /// \brief
    /// Calculate Aperture
    /// \details
    /// This function calculates the Aperature, it needs
    /// the ISO and shutterspeed which are 
    /// configured by the user. 
    float getAperture(int ISO, float shutterSpeed);

    /// \brief
    /// Get photography style shutterspeed
    /// \details
    /// This function rounds the exact shutterspeed to
    /// the closest photography-style shutterspeed
    int getCorrectShutterspeed(float x);

    /// \brief
    /// Calculate Shutterspeed
    /// \details
    /// This function calculates the Shutterspeed, it needs
    /// the aperture and ISO which are 
    /// configured by the user. 
    float getShutterspeed(float Aperture, int ISO);
};

#endif //LIGHTMETER_hpp