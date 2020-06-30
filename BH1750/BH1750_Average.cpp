// ==========================================================================
// Copyright : 2002milo@gmail.com 2020 - 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "BH1750_Average.hpp"

BH1750_Average::BH1750_Average(BH1750 & slave):
    slave( slave )
{};

uint32_t BH1750_Average::getAverageLightIntensity(const int amount){
    uint32_t total = 0;
    for(int i = 0; i < amount; i++){
        total += slave.getLightIntensity();
    }
    return total / amount;
}
