//
//  Queue Realisation for keeping maximum for each moment
//
//  queue.cpp
//  Sliding Window
//
//  Created by Илья Башаров on 22/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "queue.hpp"

MaxQueue::MaxQueue()
{}

MaxQueue::~MaxQueue()
{}

bool MaxQueue::isEmpty()
{
    return input.isEmpty() && output.isEmpty();
}

long int MaxQueue::getMax()
{
    if (input.isEmpty() || output.isEmpty())
        return input.isEmpty() ? output.getMax() : input.getMax();
    else
        return std::max(input.getMax(), output.getMax());
}

void MaxQueue::push(long int value)
{
    input.push(value);
}

long int MaxQueue::pop()
{
    if (output.isEmpty())
        while (!input.isEmpty())
        {
            long int element = input.pop();
            long int maximum = output.isEmpty() ? element : std::max(element, output.getMax());
            output.push(std::make_pair(element, maximum));
        }
    return output.pop();
}
