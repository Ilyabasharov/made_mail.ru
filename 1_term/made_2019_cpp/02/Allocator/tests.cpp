//
//  tests.cpp
//  Allocator
//
//  Created by Илья Башаров on 23/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "tests.hpp"

void test(LinearAllocator &allocator, const char* expression,
          std::size_t size_value, bool error)
{
    if (strcmp(expression, "reset") == 0)
        allocator.Reset();
    
    else if (strcmp(expression, "alloc") == 0)
    {
        char* buffer = allocator.Alloc(size_value);
        
        if (error)
        {
            assert(buffer == nullptr);
            std::cout << '.';
            return;
        }
        
        /* record testing */
        for (std::size_t i = 0; i < size_value; i++)
            buffer[i] = 'a';
        
        /* checking what was recorded */
        for (std::size_t i = 0; i < size_value; i++)
            assert(buffer[i] == 'a');
    }
    std::cout << '.';
}

void tests()
{
    LinearAllocator Allocator(10);
    
    test(Allocator, "alloc", 2, false);
    test(Allocator, "alloc", 2, false);
    test(Allocator, "alloc", 3, false);
    test(Allocator, "alloc", 1, false);
    test(Allocator, "alloc", 8, true);
    test(Allocator, "reset", 0, false);
    test(Allocator, "alloc", 5, false);
    test(Allocator, "alloc", 15, true);
    
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}
