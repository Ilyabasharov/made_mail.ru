//
//  main.cpp
//  BigInt
//
//  Created by Илья Башаров on 18/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "big_int.hpp"

int main()
{
    try
    {
        std::string d = "100";
        BigInt a = 100;
        BigInt b(d);
        BigInt c = a + b;
        std::cout << c << std::endl;
    }
    catch (const std::domain_error& de)
    {
        std::cerr << "Domain_error: " << de.what() << std::endl;
    }
    
    return 0;
}
