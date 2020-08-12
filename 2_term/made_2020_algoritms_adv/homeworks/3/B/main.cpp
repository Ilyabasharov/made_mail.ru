//
//  main.cpp
//  B
//
//  Created by Илья Башаров on 14.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>

long long* sieve(const long long number)
{
    std::vector<long long> pr;
    
    long long* lp = (long long*) calloc (number + 1, sizeof(long long)),
                   index = 0;
    
    for (long long i = 2; i <= number; i++)
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

class count_unique_deviders
{
public:
    long long unique_devider = 0;
    long long counter_deviders = 0;
    long long  muls = 1;
    long long result = 1;
};

class sum_all_deviders
{
public:
    long long local_sum = 0;
    long long local_mul = 1;
    long long muls = 1;
    long long result = 1;
};

class euler_function
{
public:
    long long muls = 1;
    long long result = 1;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    long long N = 0;
    std::cin >> N;
    
    auto lp = sieve(N);
    
    long long d = 0, index = 0;
    
    count_unique_deviders s_0;
    sum_all_deviders s_1;
    euler_function fi;
    
    for (long long i = 2; i <= N; i++)
    {
        d += lp[i];
        index = i;
        s_0.unique_devider = lp[index];
        s_0.counter_deviders = 0;
        s_0.muls = s_1.muls = s_1.local_sum = fi.muls = s_1.local_mul = 1;
        
        while (lp[index] != 0)
        {
            if (s_0.unique_devider != lp[index])
            {
                fi.muls *= s_1.local_mul / s_0.unique_devider * (s_0.unique_devider - 1);
                s_1.muls *= s_1.local_sum;
                s_0.unique_devider = s_1.local_mul = lp[index];
                s_0.muls *= s_0.counter_deviders + 1;
                s_0.counter_deviders = 1;
                s_1.local_sum = 1 + s_1.local_mul;
            }
            else
            {
                s_1.local_mul *= s_0.unique_devider;
                s_1.local_sum += s_1.local_mul;
                s_0.counter_deviders ++;
            }
            
            index = index / lp[index];
        }
        s_0.muls *= s_0.counter_deviders + 1;
        s_1.muls *= s_1.local_sum;
        fi.muls *= s_1.local_mul / s_0.unique_devider * (s_0.unique_devider - 1);
        
        s_0.result += s_0.muls;
        s_1.result += s_1.muls;
        fi.result += fi.muls;
    }
    
    free(lp);
    std::cout << d << ' ' << s_0.result << ' ' << s_1.result << ' ' << fi.result << std::endl;
    
    return 0;
}
