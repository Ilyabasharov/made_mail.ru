//
//  tests.hpp
//  Matrix
//
//  Created by Илья Башаров on 06/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include "matrix.hpp"
#include <functional>
#include <cstring>

void test(std::vector<std::vector<int>> init, std::string command,
          int value_x,
          std::vector<std::vector<int>> check, int value_y = 0);
void tests();

#endif /* tests_hpp */
