//
//  tests.cpp
//  BigInt
//
//  Created by Илья Башаров on 20/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "tests.hpp"

void test(std::string&& num1, std::string&& num2,
          int what_do, std::string&& result)
{
    BigInt a(num1);
    BigInt b(num2);
    BigInt c(result);
    switch (what_do)
    {
        case UNARY_PLUS:
            assert(+a == c);
            std::cout << '.';
            break;
            
        case ADDICTION:
            assert(a + b == c);
            std::cout << '.';
            break;
        
        case UNARY_MINUS:
            assert(-a == c);
            std::cout << '.';
            break;
        
        case SUBTRACTION:
            assert(a - b == c);
            std::cout << '.';
            break;
            
        default:
            break;
    }
}


void tests()
{
    test("10", "20", UNARY_PLUS, "10");
    test("-10", "20", UNARY_PLUS, "-10");
    test("10", "20", UNARY_MINUS, "-10");
    test("-10", "20", UNARY_MINUS, "10");
    test("10", "20", ADDICTION, "30");
    test("-10", "20", ADDICTION, "10");
    test("10", "20", SUBTRACTION, "-10");
    test("10", "-20", SUBTRACTION, "30");
    test("-10", "-20", SUBTRACTION, "10");
    
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}

int main()
{
    tests();
    return 0;
}
