//
//  heap.cpp
//  Dead ends for trains
//
//  Created by Илья Башаров on 29/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "heap.hpp"

MinHeap::MinHeap()
{}

MinHeap::~MinHeap()
{
    buffer.clear();
    std::vector<int>().swap(buffer);
}

bool MinHeap::isEmpty()
{
    return buffer.empty();
}

void MinHeap::Insert(int value)
{
    buffer.push_back(value);
    int index = static_cast<int>(buffer.size() - 1);
    
    if (index == 0)
        return;
    
    SiftUp(index);
}

int MinHeap::ExtractMin()
{
    int result = buffer.front();
    
    if (buffer.size() == 1)
    {
        buffer.clear();
        return result;
    }
    
    std::swap(buffer.front(), buffer.back());
    buffer.pop_back();
    SiftDown(0);
    
    return result;
}

void MinHeap::SiftUp(int index)
{
    int parent_index = (index + 1)/2 - 1;
    
    if (parent_index < 0 || buffer[parent_index] <= buffer[index])
        return;
    else
    {
        std::swap(buffer[parent_index], buffer[index]);
        SiftUp(parent_index);
    }
}

void MinHeap::SiftDown(int index)
{
    int left_son_index = 2*(index + 1) - 1, right_son_index = 2*(index + 1);
    if (right_son_index < buffer.size())
    {
        int min_son_index = buffer[right_son_index] > buffer[left_son_index] ?
                                      left_son_index : right_son_index;
        if (buffer[min_son_index] < buffer[index])
        {
            std::swap(buffer[min_son_index], buffer[index]);
            SiftDown(min_son_index);
        }
        return;
    }
    else if (left_son_index < buffer.size())
    {
        if (buffer[left_son_index] < buffer[index])
        {
            std::swap(buffer[left_son_index], buffer[index]);
            return;
        }
    }
    else
        return;
}

void MinHeap::print()
{
    for (auto &i : buffer)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int MinHeap::GetMin()
{
    return buffer.front();
}
