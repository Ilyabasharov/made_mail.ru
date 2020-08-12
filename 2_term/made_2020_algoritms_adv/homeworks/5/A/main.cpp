//
//  main.cpp
//  A
//
//  Created by Илья Башаров on 06.04.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>

std::int64_t pow2(const char number)
{
    std::int64_t a = 1;
    return a << number;
}

class PostfixSums
{
public:
    
    std::int64_t* sums = nullptr;
    std::int64_t n = 0;
    
public:
    PostfixSums(const std::int64_t* array, const std::int64_t& length)
    {
        n = length;
        
        fromArray(array, length);
    }
    
    std::int64_t request(const std::int64_t& l, const std::int64_t& r)
    {
        if (r < l)
            throw std::domain_error("Right bound is smaller than left bound of request.");
        
        if (r > n)
            throw std::domain_error("Right bound is bigger than the sums length.");
        
        return (l != 0) ? (sums[r] - sums[l - 1]) : sums[r];
    }
    
    void fromArray(const std::int64_t* array, const std::int64_t& length)
    {
        if (sums != nullptr)
            delete [] sums;
            
        sums = new std::int64_t[length]();
        
        sums[0] = array[0];
        
        for (std::int64_t i = 1; i < length; i++)
            sums[i] = sums[i - 1] + array[i];
    }
    
    ~PostfixSums()
    {
        delete [] sums;
    }
};

int main()
{
    std::int64_t n, x, y, a_0;
    std::int64_t pow = pow2(16);
    std::cin >> n >> x >> y >> a_0;
    
    auto a = new std::int64_t[n];
    a[0] = a_0;
    
    for (std::int64_t i = 1; i < n; i++)
        a[i] = (x*a[i - 1] + y) % pow;
    
    std::int64_t m, z, b_0;
    std::int64_t t, sums = 0;
    std::cin >> m >> z >> t >> b_0;
    
    auto b = new std::int64_t[m*2];
    b[0] = b_0;
    
    pow = pow2(30);
    
    for (std::int64_t i = 1; i < m*2; i++)
    {
        b[i] = (z*b[i - 1] + t) % pow;
        if (b[i] < 0)
            b[i] += pow;
    }
    
    for (std::int64_t i = 0; i < m*2; i++)
        b[i] = b[i] % n;
    
    
    auto postfix = PostfixSums(a, n);
    
    try
    {
        for(std::int64_t i = 0; i < m; i++)
        {
            if (b[2*i] > b[2*i + 1])
                sums += postfix.request(b[2*i + 1], b[2*i]);
            else
                sums += postfix.request(b[2*i], b[2*i + 1]);
        }
    }
    
    catch (const std::domain_error& de)
    {
        std::cerr << "Domain error: " << de.what() << std::endl;
    }
    
    std::cout << sums << std::endl;
    
    delete [] a;
    delete [] b;
    
    return 0;
}
