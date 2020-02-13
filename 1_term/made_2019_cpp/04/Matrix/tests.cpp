//
//  Test system
//
//  tests.cpp
//  Matrix
//
//  Created by Илья Башаров on 06/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "tests.hpp"

void test(std::vector<std::vector<int>> init, std::string command,
          int value_x,
          std::vector<std::vector<int>> check, int value_y)
{
    Matrix a(init);
    
    if (command == "multiply")
    {
        a *= value_x;
        assert(a == check);
    }
    else if (command == "get element")
    {
        assert(a[value_x][value_y] == check[value_x][value_y]);
    }
    std::cout << '.';
}

void tests()
{
    test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, "multiply", 1,
         {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    
    test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, "multiply", 2,
         {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
    
    test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, "get element", 2,
         {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 1);
    
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}
