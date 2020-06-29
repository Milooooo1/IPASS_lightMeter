// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef BH1750_Average_HPP
#define BH1750_Average_HPP

#include "BH1750.hpp"

/// @file

/// \brief
/// Decorator for thr BH1750
/// \details
/// This is decorator for the BH1750, it measures
/// 5 times and gives the average value, 
/// this may be helpful in conditions where the light
/// changes wildly.

class BH1750_Average : public BH1750{
private:
    BH1750 & slave; 

public:

    /// \brief
    /// Constructor 
    /// \details
    /// The constructor just needs 1 slave to get measurements from.
    BH1750_Average(BH1750 & slave);

    /// \brief
    /// Average Light intensity
    /// \details
    /// This function measures the lightintensity an x amount of times
    /// the default amount of measurments is 5.
    uint32_t getAverageLightIntensity(const int amount = 5);
};

#endif