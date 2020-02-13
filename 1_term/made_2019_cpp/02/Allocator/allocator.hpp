//
//  allocator.hpp
//  Allocator
//
//  Created by Илья Башаров on 23/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef allocator_hpp
#define allocator_hpp

#include <iostream>
#include <cstdio>

class LinearAllocator
{
public:
    LinearAllocator();
    LinearAllocator(std::size_t maxSize);
    ~LinearAllocator();
    char* Alloc(std::size_t size);
    void Reset();
    
private:
    char* buffer;
    std::size_t maxSize;
    std::size_t residue;
};

#endif /* allocator_hpp */
