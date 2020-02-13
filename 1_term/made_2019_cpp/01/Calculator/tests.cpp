//
//  Tests for Calculator
//
//  tests.cpp
//  Calculator
//
//  Created by Илья Башаров on 16/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "tests.hpp"

void test(DescentParser &calculator, const char* expression, int result, bool error)
{
    calculator.Update(expression);
    int res = calculator.RecursiveDescentParser();
    
    if (calculator.user_error == true && error == true)
    {
        std::cout << '.';
        return;
    }
    if (calculator.user_error != error)
    {
        std::cerr << "Test failed";
        return;
    }
    
    assert(res == result);
    std::cout << '.';
}

void tests(DescentParser &calculator)
{
    test(calculator, "0 + 0 + 0", 0, false);
    test(calculator, "1+1", 2, false);
    test(calculator, "1--1", 2, false);
    test(calculator, "1 * 4", 4, false);
    test(calculator, "(2+4)*(-1)", -6, false);
    test(calculator, "2 + 3 *   4  - -2", 16,false);
    test(calculator, " 2", 2, false);
    test(calculator, " -2", -2, false);
    test(calculator, " ", 1, true);
    test(calculator, "1/0", 1, true);
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}

int main()
{
    DescentParser calculator("55");
    tests(calculator);
    return 0;
}
