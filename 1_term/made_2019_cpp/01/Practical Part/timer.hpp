//
//  Realisation timer for time counting
//
//  timer.hpp
//  Practical Part
//
//  Created by Илья Башаров on 16/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <chrono>
#include <iostream>

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer();
    ~Timer();

private:
    const clock_t::time_point start_;
};

#endif /* timer_hpp */
