//
//  Program supports recursive descent parser for calculating:
//
//  -> addition or subtraction;
//  -> multiplying or division;
//  -> priority which used brackets;
//  -> unary minus.
//
//  Input: command line string with ints and available functions
//  Output: int
//
//  main.cpp
//  Calculator
//
//  Created by Илья Башаров on 15/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "calculation.hpp"

int main(int argc, const char * argv[])
{
    DescentParser calculator(argv[1]);
    int result = calculator.RecursiveDescentParser();
    if (calculator.user_error)
    {
        std::cerr << "You should write string correctly" << std::endl;
        return ERROR_CODE;
    }
    std::cout << result << std::endl;
    return 0;
}
