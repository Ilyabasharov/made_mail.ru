//
//  main.cpp
//  B
//
//  Created by Илья Башаров on 23.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <unordered_map>

long long mul(long long a, long long b, long long m)
{
    long long q = static_cast<long double>(a) * static_cast<long double>(b) / static_cast<long double>(m);
    long long r = a * b - q * m;
    
    return (r + 5 * m) % m;
}

int main()
{
    long long a, b, m;
    std::cin >> a >> b >> m;
    
    std::unordered_map<long long, long long> set;
    
    long long an = 1, i, k, current;
    
    for (i = 0; i*i < m; ++i)
        an = mul(an, a, m);
    
    k = i;
    
    for (i = 1, current = an; i <= k; ++i)
    {
        if (set.find(current) == set.end())
            set[current] = i;
        
        current = mul(current, an, m);
    }
    
    for (i = 0, current = b; i <= k; ++i)
    {
        auto iterator = set.find(current);
        
        if (iterator != set.end())
        {
            long long ans = iterator -> second * k - i;
            
            if (ans < m)
            {
                std::cout << ans << std::endl;
                return 0;
            }
        }
        
        current = mul(current, a, m);
    }
    
    std::cout << -1 << std::endl;
    
    return 0;
}
