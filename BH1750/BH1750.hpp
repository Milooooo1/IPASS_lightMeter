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
private:
    uint8_t address;
    //hwlib::target::pin_out addr_pin; // = hwlib::target::pin_out( hwlib::pin_out_dummy );
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
    //TODO add addr_pin
    /// \brief
    /// Constructor
    /// \details
    /// The constructor has the option to use 1 of 2 I2C addresses
    /// default address is 0x23, this is used in combination with
    /// the high resolution mode which is standard in this library
    /// you also have the option to add an addr pin which is necessary
    /// in combination with multiple BH1750 chips.
    BH1750(uint8_t address = 0x23);

    /// \brief
    /// Power down
    /// \details
    /// This function preserves battery life by giving it
    /// no active state which means its 'sleeping'.
    void PowerDown();

    /// \brief
    /// Power on
    /// \details
    /// This function makes the chip wait for a measurment 
    /// command, it wakes the device up if its 'sleeping'.
    void PowerOn();

    /// \brief
    /// Reset
    /// \details
    /// This function resets the data stored in the registers.
    void Reset();

    /// \brief
    /// Configure mode
    /// \details
    /// This function configures the mode which is used
    /// by the chip how to measure the light value.
    void Configure(MODE mode);

    /// \brief
    /// Measure light intensity
    /// \details
    /// This function returns the measured light intensity
    /// the value is measured in LUX. 
    uint16_t GetLightIntensity(void);   

};   

#endif //BH1750_HPP