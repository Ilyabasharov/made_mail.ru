//
//  main.cpp
//  A
//
//  Created by Илья Башаров on 14.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>

unsigned long* sieve(const unsigned long number)
{
    std::vector<unsigned long> pr;
    
    unsigned long* lp = (unsigned long*) calloc (number + 1, sizeof(unsigned long)),
                   index = 0;
    
    for (unsigned long i = 2; i <= number; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        
        for (auto prime : pr)
        {
            index = i*prime;
            
            if (prime > lp[i] || index > number)
                break;
            
            lp[index] = prime;
        }
    }
    
    return lp;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    unsigned long N = 0, max = 0;
    std::cin >> N;
    unsigned long* numbers = (unsigned long*) calloc (N, sizeof(unsigned long));
    
    for (unsigned long i = 0; i < N; i++)
    {
        std::cin >> numbers[i];
        if (numbers[i] > max)
            max = numbers[i];
    }
    
    auto lp = sieve(max);
    
    for (unsigned long i = 0; i < N; i++)
    {
        unsigned long index = numbers[i];
        
        while (lp[index] != 0)
        {
            std::cout << lp[index] << ' ';
            index = index / lp[index];
        }
        std::cout << '\n';
    }
    
    free(lp);
    free(numbers);
    
    return 0;
}
