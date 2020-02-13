//
//  tests.hpp
//  Sorting long sequence
//
//  Created by Илья Башаров on 31/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include <vector>
#include <functional>
#include <cassert>
#include <algorithm>
#include <cstdlib>

void test(std::function<std::vector<long int>(unsigned int n)> a,
          unsigned int n, unsigned int k);
void tests();

#endif /* tests_hpp */
