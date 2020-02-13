//
//  main.cpp
//  Matrix
//
//  Created by Илья Башаров on 05/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "tests.hpp"

int main()
{
    try
    {
        tests();
    }
    catch (const std::length_error& le)
    {
        std::cerr << "Length error: " << le.what() << std::endl;
    }
    catch (const std::out_of_range& oof)
    {
        std::cerr << "Out of range: " << oof.what() << std::endl;
    }
    
    return 0;
}
