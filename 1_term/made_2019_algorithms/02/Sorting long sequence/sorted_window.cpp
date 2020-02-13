//
//  sorted_window.cpp
//  Sorting long sequence
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "sorted_window.hpp"

bool cmp(long int a, long int b)
{
    return a < b ? true : false;
}

void my_qsort(std::vector<long int>::iterator first,
              std::vector<long int>::iterator last,
              std::function<bool(long int a, long int b)> compare)
{
    if(first != last)
    {
        auto left  = first;
        auto right = last;
        auto pivot = left++;
        
        while (left != right)
        {
            
            if (compare(*left, *pivot))
                ++left;
            else
            {
                while ((left != --right) && compare(*pivot, *right));
                std::iter_swap(left, right);
            }
        }
        
        --left;
        std::iter_swap(first, left);
        my_qsort(first, left, compare);
        my_qsort(right, last, compare);
    }
}

SortedWindow::SortedWindow(std::vector<long int> &buffer):
window(buffer)
{
    my_qsort(window.begin(), window.end(), cmp);
}

SortedWindow::~SortedWindow()
{}

void SortedWindow::AnalyseFirstKMinElements(std::vector<long int> &buffer)
{
    my_qsort(buffer.begin(), buffer.end(), cmp);
    
    std::vector<long int> current(window.size(), 0);
    unsigned long int it_window = 0, it_buffer = 0;
    
    for (unsigned long int i = 0; i < window.size(); i ++)
    {
        if (it_buffer < buffer.size())
            current[i] = window[it_window] > buffer[it_buffer] ?
                    buffer[it_buffer++] : window[it_window++];
        else
            current[i] = window[it_window++];
    }
    
    for (unsigned long int i = 0; i < window.size(); i ++)
        window[i] = current[i];
}

void SortedWindow::PrintWindow()
{
    for (auto& object : window)
        std::cout << object << ' ';
    
    std::cout << std::endl;
}

long int SortedWindow::GetElement(int index)
{
    return window[index];
}
