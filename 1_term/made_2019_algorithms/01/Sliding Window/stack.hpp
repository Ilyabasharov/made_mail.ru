//
//  Stack Realisation for keeping maximum for each moment
//
//  stack.hpp
//  Sliding Window
//
//  Created by Илья Башаров on 22/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

class MaxStack
{
public:
    long int pop();
    void push(long int value);
    void push(std::pair<long int, long int> value);
    bool isEmpty();
    long int getMax();
    ~MaxStack();
    MaxStack();
    
private:
    std::vector<std::pair<long int, long int>> stack;
};

#endif /* stack_hpp */
