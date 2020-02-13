//
//  Queue Realisation for keeping maximum for each moment
//
//  queue.hpp
//  Sliding Window
//
//  Created by Илья Башаров on 22/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include "stack.hpp"

class MaxQueue
{
private:
    MaxStack input;
    MaxStack output;
    
public:
    MaxQueue();
    ~MaxQueue();
    void push(long int value);
    long int pop();
    long int getMax();
    bool isEmpty();
};

#endif /* queue_hpp */
