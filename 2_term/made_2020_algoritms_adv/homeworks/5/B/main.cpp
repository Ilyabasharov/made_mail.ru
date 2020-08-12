//
//  main.cpp
//  B
//
//  Created by Илья Башаров on 10.04.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>

class FenwickTree
{
private:
    std::int64_t* fenwick_sums = nullptr;
    std::int64_t* initial = nullptr;
    std::uint64_t length = 0;
    
public:
    
    FenwickTree(std::int64_t* array, const std::uint64_t& n)
    {
        length = n;
        initial = array;
        
        fenwick_sums = new std::int64_t[length]();
        
        fenwick_sums[0] = initial[0];
        
        for(std::uint64_t i = 1; i < length; i++)
            fenwick_sums[i] = fenwick_sums[i - 1] + initial[i];
        
        std::int64_t temp = 0;
        
        for(std::uint64_t i = length - 1; i > 0; i--)
        {
            temp = f(i) - 1;
            if (temp >= 0)
                fenwick_sums[i] -= fenwick_sums[temp];
        }
    }
    
    std::int64_t get(std::int64_t i)
    {
        std::int64_t res = 0;
        
        while (i >= 0)
        {
            res += fenwick_sums[i];
            i = f(i) - 1;
        }
        
        return res;
    }
    
    std::int64_t rsq_request(const std::int64_t& l, const std::int64_t& r)
    {
        return (l == 0) ? get(r) : get(r) - get(l - 1);
    }
    
    void add(const std::int64_t& i, const std::int64_t& x)
    {
        std::int64_t j = i;
        
        while (j < length)
        {
            fenwick_sums[j] += x;
            j = j | (j + 1);
        }
    }
    
    void set(const std::int64_t& i, const std::int64_t& x)
    {
        std::int64_t d = x - initial[i];
        initial[i] = x;
        
        add(i, d);
    }
    
    std::int64_t f(const std::int64_t& i)
    {
        return i & (i + 1);
    }
    
    ~FenwickTree()
    {
        delete [] fenwick_sums;
        delete [] initial;
        length = 0;
    }
};

int main()
{
    std::uint64_t n = 0;
    std::cin >> n;
    
    auto array = new std::int64_t[n]();
    
    for (std::uint64_t i = 0; i < n; i++)
        std::cin >> array[i];
    
    auto fenwick = FenwickTree(array, n);
    
    std::string command;
    std::uint64_t a, b;
    
    while (std::cin >> command >> a >> b)
    {
        if (command == "sum")
            std::cout << fenwick.rsq_request(a - 1, b - 1) << std::endl;
        else
            fenwick.set(a - 1, b);
    }
    
    return 0;
}
