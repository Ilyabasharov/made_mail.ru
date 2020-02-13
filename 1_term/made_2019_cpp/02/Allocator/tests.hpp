//
//  tests.hpp
//  Allocator
//
//  Created by Илья Башаров on 23/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include <cassert>
#include "allocator.hpp"

void test(LinearAllocator &allocator, const char* expression,
          std::size_t size_value, bool error);
void tests();

#endif /* tests_hpp */
