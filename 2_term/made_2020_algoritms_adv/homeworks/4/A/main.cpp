//
//  main.cpp
//  A
//
//  Created by Илья Башаров on 23.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>

std::vector<long long> find_devisors(long long p)
{
    std::vector<long long> divisors;
    
    long long init_p = p;
    
    for (long long i = 2; i*i <= p; i++)
        while (p % i == 0)
        {
            divisors.push_back(init_p / i);
            p /= i;
        }
    
    if (p != 1)
        divisors.push_back(init_p / p);
    
    return divisors;
}

long long pow_mod(long long a, long long b, long long p)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % p;

        a = a * a % p;
        b >>= 1;
    }
        
    return res;
}

int main()
{
    long long p = 0;
    std::cin >> p;
    
    auto divisors = find_devisors(p - 1);
    
    bool is_root = true;
    
    for (long long i = 2; i <= p; i++)
    {
        is_root = true;
        for (const auto devisor : divisors)
            if (pow_mod(i, devisor, p) == 1)
            {
                is_root = false;
                break;
            }
        
        if (is_root)
        {
            std::cout << i << std::endl;
            break;
        }
    }
    
    return 0;
}
