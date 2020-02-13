//
//  queue.cpp
//  Queue with dynamic buffer
//
//  Created by Илья Башаров on 18/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "queue.hpp"

QueueWithDynamicBuffer::QueueWithDynamicBuffer()
{}

QueueWithDynamicBuffer::~QueueWithDynamicBuffer()
{
    free(buffer);
    buffer = nullptr;
    capasity = 0;
    size = 0;
}

void QueueWithDynamicBuffer::allocate()
{
    long int* current_data = (long int*) calloc (2*(++size), sizeof(long int));
    size *= 2;
    
    for (unsigned long int i = 0; i < capasity; i++)
        current_data[i] = buffer[(iter_pop + i)%capasity];
    
    iter_pop = 0;
    if (!buffer)
        free(buffer);
    buffer = current_data;
    iter_push = capasity;
}

void QueueWithDynamicBuffer::push_back(long int value)
{
    if (size == capasity || size == 0)
        allocate();
    
    buffer[iter_push %= size] = value;
    iter_push +=1;
    capasity +=1;
}

long int QueueWithDynamicBuffer::pop_front()
{
    if (capasity == 0)
        return -1;
    
    iter_pop %= size;
    capasity -= 1;
    return buffer[iter_pop++];
}
