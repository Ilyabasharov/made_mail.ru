//
//  main.cpp
//  E task
//
//  Created by Илья Башаров on 01.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <limits>

int howManyTimesMinInRow(int** matrix, unsigned int dimension, unsigned int row, int* min)
{
    *min = matrix[row][0];
    
    for (unsigned int i = 1; i < dimension; i++)
        if (matrix[row][i] < *min)
            *min = matrix[row][i];
    
    int result = 0;
    
    for (unsigned int i = 0; i < dimension; i++)
        if (matrix[row][i] == *min)
            result ++;
    
    return result - 1;
}

int sum(int a, int b)
{
    if (a == std::numeric_limits<int>::max() || b == std::numeric_limits<int>::max())
        return std::numeric_limits<int>::max();
    else
        return a + b;
}

int main()
{
    unsigned int N = 0;
    std::cin >> N;
    
    int* costs = (int*) calloc(N, sizeof(int));
    int* days = (int*) calloc(N, sizeof(int));
    int** matrix = (int**) calloc(N + 1, sizeof(int*));
    
    for (unsigned int i = 0; i < N + 1; i++)
        matrix[i] = (int*) calloc(N + 1, sizeof(int));
    
    for (unsigned int i = 0; i < N; i++)
    {
        std::cin >> costs[i];
        matrix[0][i + 1] = std::numeric_limits<int>::max();
    }
    
    for (unsigned int i = 1; i < N + 1; i++)
    {
        matrix[i][0] = std::min(sum(matrix[i - 1][0], costs[i - 1]), matrix[i - 1][1]);
        
        for (unsigned int j = 1; j < N; j++)
            
            matrix[i][j] = std::min(sum(matrix[i - 1][j - (costs[i - 1] > 100)], costs[i - 1]),
                                    matrix[i - 1][j + 1]);
        
        matrix[i][N] = sum(matrix[i - 1][N - (costs[i - 1] > 100)], costs[i - 1]);
    }
    
    int min = 0, k1 = howManyTimesMinInRow(matrix, N + 1, N, &min), counter = 0, min_index = k1, min_equal = k1;
    std::cout << min << '\n' << k1 << ' ';
    
    for (int i = N, j = k1; i > 1; i--)
    {
        min_equal = -1;
        for (int shift = j - 1; shift <= j + 1; ++shift)
        {
            if (shift < 0 || shift > N || matrix[i - 1][shift] == std::numeric_limits<int>::max())
                continue;
            
            if (matrix[i - 1][shift] == min)
                min_equal = shift;
            else if (matrix[i - 1][shift] + costs[i - 1] == min)
                min_index = shift;
        }
        
        if (min_equal - j > 0)
        {
            days[counter++] = i;
            min_index = min_equal;
        }
        min = matrix[i - 1][min_index];
        j = min_index;
    }
    
    std::cout << counter << '\n';
    for (int i = counter - 1; i >= 0; i--)
        std::cout << days[i] << '\n';
    
    free(costs);
    free(days);
    
    for (unsigned int i = 0; i < N + 1; i++)
        free(matrix[i]);
    
    free(matrix);
    
    return 0;
}
