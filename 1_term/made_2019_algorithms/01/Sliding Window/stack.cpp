//
//  Stack Realisation for keeping maximum for each moment
//
//  stack.cpp
//  Sliding Window
//
//  Created by Илья Башаров on 22/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "stack.hpp"

MaxStack::MaxStack()
{}

MaxStack::~MaxStack()
{
    stack.clear();
    std::vector<std::pair<long int, long int>>().swap(stack);
}

long int MaxStack::pop()
{
    long int value = stack.back().first;
    stack.pop_back();
    return value;
}

void MaxStack::push(long int value)
{
    long int maximum = stack.empty() ? value : std::max(value, stack.back().second);
    stack.push_back(std::make_pair(value, maximum));
}

void MaxStack::push(std::pair<long int, long int> value)
{
    stack.push_back(value);
}

bool MaxStack::isEmpty()
{
    return stack.empty();
}

long int MaxStack::getMax()
{
    return stack.back().second;
}
