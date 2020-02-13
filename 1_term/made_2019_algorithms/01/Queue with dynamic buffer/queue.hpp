//
//  queue.hpp
//  Queue with dynamic buffer
//
//  Created by Илья Башаров on 18/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <iostream>

class QueueWithDynamicBuffer
{
private:
    long int* buffer = nullptr;
    unsigned long int iter_pop = 0;
    unsigned long int iter_push = 0;
    unsigned long int capasity = 0;
    unsigned long int size = 0;
    
public:
    void push_back(long int value);
    long int pop_front();
    void allocate();
    
    QueueWithDynamicBuffer();
    ~QueueWithDynamicBuffer();
};

#endif /* queue_hpp */
