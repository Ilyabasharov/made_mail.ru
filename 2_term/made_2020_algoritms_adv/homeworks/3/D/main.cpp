//
//  main.cpp
//  D
//
//  Created by Илья Башаров on 15.03.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>

long long updated_gcd(long long a, long long b, long long& x, long long& y)
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
 
bool solution(long long a, long long b, long long c,
              long long& x0, long long& y0, long long& g)
{
    g = updated_gcd(a, b, x0, y0);
    
    if (c % g != 0)
        return false;
    
    x0 *= c / g;
    y0 *= c / g;
    
    return true;
}

int main()
{
    long long A = 0, B = 0, C = 0, x0 = 0, y0 = 0, g = 0;
    std::cin >> A >> B >> C;
    
    if (solution(A, B, -C, x0, y0, g))
        std::cout << x0 << ' ' << y0;
    else
        std::cout << -1;
        
    return 0;
}
