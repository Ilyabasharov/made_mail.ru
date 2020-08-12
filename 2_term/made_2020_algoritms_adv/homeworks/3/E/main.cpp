//
//  main.cpp
//  E
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
    
    long long x1 = 0, y1 = 0, d = updated_gcd(b%a, a, x1, y1);
    
    x = y1 - (b / a) * x1;
    y = x1;
    
    return d;
}

long long inverse_element(long long element, long long mod)
{
    long long x, y;
    updated_gcd(element, mod, x, y);
    return (x % mod + mod) % mod;
}

long long garner_algorithm(long long k, long long* a, long long* r)
{
    long long **r_matrix = (long long**) calloc(k, sizeof(long long*));
    
    for (long long i = 0; i < k; i++)
    {
        r_matrix[i] = (long long*) calloc(k, sizeof(long long));
        
        for (long long j = 0; j < k; j++)
            r_matrix[i][j] = inverse_element(a[i], a[j]);
    }
    
    long long *x = (long long*) calloc(k, sizeof(long long));
    
    for (long long i = 0; i < k; i++)
    {
        x[i] = r[i];
        
        for (long long j = 0; j < i; j++)
        {
            x[i] = (r_matrix[j][i] * (x[i] - x[j])) % a[i];
            
            if (x[i] < 0)
                x[i] += a[i];
        }
    }
    
    long long result = 0, mul = 1;
    
    for (long long i = 0; i < k; i++)
    {
        result += mul*x[i];
        mul *= a[i];
        free(r_matrix[i]);
    }
    
    free(r_matrix);
    free(x);
    
    return result;
}

int main()
{
    unsigned int N;
    std::cin >> N;
    
    long long a[2], r[2];
    
    for (unsigned int i = 0; i < N; i++)
    {
        std::cin >> r[0] >> r[1] >> a[0] >> a[1];
        std::cout << garner_algorithm(2, a, r) << '\n';
    }
    
    return 0;
}
