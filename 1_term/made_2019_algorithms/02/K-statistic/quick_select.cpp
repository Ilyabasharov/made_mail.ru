//
//  Quick Select algorithm realisation with
//  randomly choosing the pivot element
//
//  quick_select.cpp
//  K-statistic
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "quick_select.hpp"

unsigned long int Partition(std::vector<int> &buffer,
                            const unsigned long int left,
                            const unsigned long int right)
{
    unsigned long int i = 0, j = 0;
    int pivot = buffer[right];
    while (j < right)
    {
        if (buffer[j] > pivot)
            j++;
        else
            std::swap(buffer[j++], buffer[i++]);
    }
    std::swap(buffer[i], buffer[right]);
    
    return i;
}

unsigned long int RandomPivotPartition(std::vector<int> &buffer,
                                       const unsigned long int left,
                                       const unsigned long int right)
{
    unsigned long int pivot_index = std::rand() % (right - left + 1) + left;
    std::swap(buffer[pivot_index], buffer[right]);
    return Partition(buffer, left, right);
}

int QuickSelect(std::vector<int> &buffer, const unsigned int k)
{
    unsigned long int left = 0, right = buffer.size() - 1;
    while (true)
    {
        unsigned long int mid = RandomPivotPartition(buffer, left, right);
        if (mid == k)
            return buffer[mid];
        if (mid > k)
            right = mid;
        else
            left = mid + 1;
    }
}
