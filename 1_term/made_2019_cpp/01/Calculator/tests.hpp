//
//  tests.hpp
//  Calculator
//
//  Created by Илья Башаров on 16/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include <iostream>
#include <cassert>
#include "calculation.hpp"

void test(DescentParser &calculator, const char* expression, int result);
void tests(DescentParser &calculator);

#endif /* tests_hpp */
