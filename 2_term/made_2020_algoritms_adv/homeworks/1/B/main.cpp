//
//  main.cpp
//  A task
//
//  Created by Илья Башаров on 27.02.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>

int main()
{
    long int N = 0, M = 0;
    std::cin >> N >> M;
    
    std::vector<std::vector<long int>> money(N, std::vector<long int>(M, 0)),
                                       max_money(N, std::vector<long int>(M, 0));
    
    for (long int i = 0; i < N; ++i)
        for (long int j = 0; j < M; ++j)
            std::cin >> money[i][j];
    
    for (long int i = 0; i < N; i++)
        for (long int j = 0; j < M; j++)
        {
            if (i == 0 && j > 0)
                max_money[i][j] = max_money[i][j - 1] + money[i][j];
            else if (i > 0 && j == 0)
                max_money[i][j] = max_money[i - 1][j] + money[i][j];
            else if (i > 0 && j > 0)
                max_money[i][j] = std::max(max_money[i][j - 1], max_money[i - 1][j]) + money[i][j];
            else
                max_money[i][j] = money[i][j];
        }
    
    long int i = N - 1, j = M - 1;
    std::vector<char> steps(N + M - 2);
    
    for (long int iterator = N + M - 3; iterator >= 0; iterator--)
    {
        if (i > 0 && j > 0)
        {
            if (max_money[i][j - 1] > max_money[i - 1][j])
            {
                steps[iterator] = 'R';
                j -= 1;
            }
            else
            {
                steps[iterator] = 'D';
                i -= 1;
            }
        }
        else if (i == 0 && j > 0)
        {
            steps[iterator] = 'R';
            j -= 1;
        }
        else if (j == 0 && i > 0)
        {
            steps[iterator] = 'D';
            i -= 1;
        }
    }
    
    std::cout << max_money[N - 1][M - 1] << std::endl;
    
    for (auto element : steps)
        std::cout << element;
    
    std::cout << std::endl;
    
    return 0;
}
