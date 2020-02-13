//
//  Practical Part from cpp seminar
//
//  sum_by_rows.cpp
//  Practical Part
//
//  Created by Илья Башаров on 16/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include <iostream>
#include <vector>
#include "timer.hpp"

std::vector<int> sum_by_rows(std::vector<int> &matrix, long int X, long int Y)
{
    Timer t;
    std::vector<int> sums(X, 0);
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            sums[i] += matrix[i*Y+j];
        }
    }
    t.~Timer();
    return sums;
}

int main()
{
    long int X = 10000;
    long int Y = 10000;
    std::vector<int> matrix(X*Y, 0);
    std::vector<int> result;
    for (int i = 0; i<50; i++)
        std::vector<int> result = sum_by_rows(matrix, X, Y);
    
    return 0;
}
