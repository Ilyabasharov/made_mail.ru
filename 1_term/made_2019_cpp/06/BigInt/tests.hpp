//
//  tests.hpp
//  BigInt
//
//  Created by Илья Башаров on 20/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include "big_int.hpp"
#include <cassert>

typedef enum : unsigned
{
    UNARY_PLUS,
    ADDICTION,
    UNARY_MINUS,
    SUBTRACTION,
    LESS,
    LESS_EQUAL,
    MORE,
    MORE_EQUAL,
    NOT_EQUAL,
    EQUAL
} Actions;

void test(std::string& num1, std::string& num2,
          unsigned int what_do, std::string& result);
void tests();

#endif /* tests_hpp */
