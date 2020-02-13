//
//  allocator.cpp
//  Allocator
//
//  Created by Илья Башаров on 23/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "allocator.hpp"

LinearAllocator::LinearAllocator()
{}

LinearAllocator::LinearAllocator(std::size_t maxSize_):
buffer(new char[maxSize_]),
maxSize(maxSize_), residue(maxSize_)
{}

LinearAllocator::~LinearAllocator()
{
    buffer -= maxSize - residue;
    delete [] buffer;
    
    buffer = nullptr;
    maxSize = 0;
}

char* LinearAllocator::Alloc(std::size_t size)
{
    if (size > residue || size == 0)
        return nullptr;
    
    char* current_buffer = buffer;
    buffer += size;
    residue -= size;
    
    return current_buffer;
}

void LinearAllocator::Reset()
{
    buffer -= maxSize - residue;
    residue = maxSize;
}
