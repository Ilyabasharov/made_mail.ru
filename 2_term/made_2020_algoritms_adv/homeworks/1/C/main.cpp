//
//  main.cpp
//  C task
//
//  Created by Илья Башаров on 29.02.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>

int main()
{
    std::size_t N = 0, i = 0;
    std::cin >> N;
    
    long int* array = (long int*) calloc(N, sizeof(long int)),
              *dp = (long int*) calloc(N, sizeof(long int)),
              *p = (long int*) calloc(N, sizeof(long int));
    
    for (i = 0; i < N; i++)
        std::cin >> array[i];
    
    for (i = 0; i < N; i++)
    {
        dp[i] = 1; p[i] = -1;
        for (std::size_t j = 0; j < i; j++)
            if (array[j] < array[i])
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    p[i] = j;
                }
    }
    
    long int answer = dp[0], end_position = 0;
    for (i = 0; i < N; i++)
        if (dp[i] > answer)
        {
            answer = dp[i];
            end_position = i;
        }
    
    std::cout << answer << std::endl;
    
    for (i = 0; i < N && end_position != -1; i++)
    {
        dp[i] = end_position;
        end_position = p[end_position];
    }
    
    free(p);
    
    for (long int j = i - 1; j >= 0; j--)
        std::cout << array[dp[j]] << ' ';
    
    free(array);
    free(dp);
    
    return 0;
}
