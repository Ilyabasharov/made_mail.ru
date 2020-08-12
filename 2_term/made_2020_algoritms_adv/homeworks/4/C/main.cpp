//
//  main.cpp
//  C
//
//  Created by Илья Башаров on 24.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>

long long mul_mod(long long a, long long b, long long m)
{
    long long q = static_cast<long double>(a) * static_cast<long double>(b) / static_cast<long double>(m),
              r = a * b - q * m;
    
    return (r + 5 * m) % m;
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

long long updated_gcd(long long a, long long b,
                      long long& x, long long& y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    long long x1 = 0, y1 = 0, d = updated_gcd(b % a, a, x1, y1);
    
    x = y1 - (b / a) * x1;
    y = x1;
    
    return d;
}

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

long long find_generator(long long p)
{
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
            return i;
    }
    
    return -1;
}

long long find_log_mod(long long a, long long b, long long m)
{
    std::unordered_map<long long, long long> set;
    
    long long an = 1, i, k, current;
    
    for (i = 0; i*i < m; ++i)
        an = mul_mod(an, a, m);
    
    k = i;
    
    for (i = 1, current = an; i <= k; ++i)
    {
        if (set.find(current) == set.end())
            set[current] = i;
        
        current = mul_mod(current, an, m);
    }
    
    for (i = 0, current = b; i <= k; ++i)
    {
        auto iterator = set.find(current);
        
        if (iterator != set.end())
        {
            long long ans = iterator -> second * k - i;
            
            if (ans < m)
                return ans;
        }
        
        current = mul_mod(current, a, m);
    }
    
    return -1;
}

bool linear_mod_equation(long long a, long long b, long long c,
                         long long& x0, long long& y0)
{
    long long g = updated_gcd(a, b, x0, y0);
    
    if (c % g != 0)
        return false;
    
    x0 *= c / g;
    y0 *= c / g;
    
    return true;
}

int main()
{
    std::size_t T;
    std::cin >> T;
    
    long long b, k, p, x0, y0, gen;
    
    for (std::size_t i = 0; i < T; i++)
    {
        std::cin >> b >> k >> p;
        
        gen = find_generator(p);

        long long s = find_log_mod(gen, b, p);
        
        if (s == -1)
        {
            std::cout << -1 << "find_log_mod" << '\n';
            continue;
        }
        
        if (!linear_mod_equation(k, p - 1, s % (p - 1), x0, y0))
        {
            std::cout << -1 << '\n';
            continue;
        }
        
        if (x0 < 0)
            x0 += -(x0 / (p - 1))*(p-1) + p - 1;
        
        std::cout << pow_mod(gen, x0, p) << '\n';
    }
    
    return 0;
}
