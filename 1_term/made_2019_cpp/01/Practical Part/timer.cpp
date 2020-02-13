//
//  timer.cpp
//  Practical Part
//
//  Created by Илья Башаров on 16/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "timer.hpp"

Timer::Timer():
start_(clock_t::now())
{}

Timer::~Timer()
{
    const auto finish = clock_t::now();
    const auto us =
        std::chrono::duration_cast<microseconds>
            (finish - start_).count();
    std::cout << us << " us" << std::endl;
}
