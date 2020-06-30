// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef BH1750_HPP
#define BH1750_HPP

#include "hwlib.hpp"
#include <stdint.h>

/// @file

/// \brief
/// BH1750 C++ Library
/// \details
/// This is a C++ Library implementing the BH1750 
/// light intensity sensor. It is using the hwlib I2C
/// implementation to communicate with the chip. 
///
/// The hwlib documentation and library can be found 
/// on github here: https://github.com/wovo/hwlib. 

class BH1750 {
protected:
    uint8_t address;
    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

public:

    /// \brief
    /// enum for the different states
    /// \details
    /// This enum makes it easier to read which state or 
    /// opecode is being sent to the chip.
    enum STATE
    {
        POWER_DOWN = 0x00,
        POWER_UP = 0x01,
        RESET = 0x07,
    };

    /// \brief
    /// enum for the different modes
    /// \details
    /// This enum makes it easier to read which mode or 
    /// opecode is being sent to the chip.
    enum MODE
    {
        CONTINUOUSLY_H_RES = 0x10,
        CONTINUOUSLY_H_RES2 = 0x11,
        CONTINUOUSLY_L_RES = 0x13,
        ONE_TIME_H_RES = 0x20,
        ONE_TIME_H_RES2	= 0x21,
        ONE_TIME_L_RES = 0x23
    };

    /// \brief
    /// enum for the different measurement times
    /// \details
    /// This enum makes it easier to read how sensitive 
    /// the sensor is. It changes how long the optical
    /// window is opened. 
    enum MTREGT_MODES
    {
        DEFAULT_MTREG = 0x45,
        MIN_MTREG     = 0x1F,
        MAX_MTREG     = 0xFE
    };

    /// \brief
    /// Constructor
    /// \details
    /// The constructor has a default address is 0x23 
    /// this is used in combination with the high resolution mode 
    /// this is standard in this library you can also choose the 
    /// low resolution mode: 0x5C.
    BH1750(uint8_t address = 0x23);

    /// \brief
    /// Power down
    /// \details
    /// This function preserves battery life by giving it
    /// no active state which means its 'sleeping'.
    void powerDown();

    /// \brief
    /// Power on
    /// \details
    /// This function makes the chip wait for a measurment 
    /// command, it wakes the device up if its 'sleeping'.
    void powerOn();

    /// \brief
    /// Reset
    /// \details
    /// This function resets the data stored in the registers.
    void reset();

    /// \brief
    /// Configure mode
    /// \details
    /// This function configures the mode which is used
    /// by the chip how to measure the light value.
    void configure(MODE mode);

    /// \brief
    /// Configure measurement time
    /// \details
    /// This function adds the ability to change
    /// the measurement time (MTreg = measurment register)
    /// this changes the sensitivity of the sensor. 
    void configureMTREG(MTREGT_MODES mode);

    /// \brief
    /// Measure light intensity
    /// \details
    /// This function returns the measured light intensity
    /// the value is measured in LUX. 
    uint16_t getLightIntensity();   

};   

#endif //BH1750_HPP
