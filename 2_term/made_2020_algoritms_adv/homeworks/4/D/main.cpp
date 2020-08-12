//
//  main.cpp
//  D
//
//  Created by Илья Башаров on 24.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>

std::uint64_t mul_mod(std::uint64_t a, std::uint64_t b, std::uint64_t m)
{
    std::uint64_t q = static_cast<long double>(a) * static_cast<long double>(b) / static_cast<long double>(m);
    std::uint64_t r = a * b - q * m;
    
    return (r + 5 * m) % m;
}

std::uint64_t pow_mod(std::uint64_t a, std::uint64_t b, const std::uint64_t& p)
{
    std::uint64_t res = 1;
    
    a %= p;
    
    while (b)
    {
        if (b & 1)
            res = mul_mod(res, a, p);

        a = mul_mod(a, a, p);
        b >>= 1;
    }
        
    return res;
}

bool miller_rabin_test(const std::uint64_t& number, const std::size_t rounds)
{
    if (number < 6)
        return (number == 1 || number == 4) ? false : true;
    
    std::uint64_t pow, current, random_number;
    
    for (std::size_t i = 0; i < rounds; i++)
    {
        random_number = static_cast<std::uint64_t>(std::rand() % (number - 2) + 2);
        current = number - 1;
        
        pow = pow_mod(random_number, current, number);
        
        if (pow != 1 && pow != number - 1)
            return false;
        
        while (current % 2 == 0)
        {
            current /= 2;
            
            pow = pow_mod(random_number, current, number);
            
            if (pow != 1)
            {
                if (pow == number - 1)
                    break;
                else
                    return false;
            }
                
        }
    }
    
    return true;
}

bool isPrime(std::uint64_t number)
{
    bool is_prime = true;
    
    for(std::uint64_t i = 2; i <= number / 2; ++i)
    {
        if(number % i == 0)
        {
            is_prime = false;
            break;
        }
    }
    
    return is_prime;
}

int main()
{
    std::size_t n;
    std::cin >> n;
    
    std::srand(static_cast<std::uint32_t>(std::time(0)));
    
    std::uint64_t number;
    
    for (std::uint64_t i = 0; i < n; i ++)
    {
        std::cin >> number;
        miller_rabin_test(number, 6) ? std::cout << "YES" << '\n' :
                                   std::cout << "NO" << '\n';
    }
    
    return 0;
}
