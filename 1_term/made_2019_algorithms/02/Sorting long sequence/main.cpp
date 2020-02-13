//
//  The program can keep first k minimal elements of long long sequence.
//  Memory usage is O(k), time complexity is (n*log(k)).
//
//  main.cpp
//  Sorting long sequence
//
//  Created by Илья Башаров on 29/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "sorted_window.hpp"

int main()
{
    unsigned long int k = 0, n = 0;
    std::cin >> n >> k;
    long int value = 0;
    
    if (n < 1 || k <= 0 || k > n)
        return 0;
    
    unsigned long int dim = n / k;
    std::vector<long int> buffer(k, 0);
    
    for (unsigned long int j = 0; j < k; j++)
    {
        std::cin >> value;
        buffer[j] = value;
    }
    
    SortedWindow window(buffer);
    
    for (unsigned long int i = 0; i < dim - 1; i++)
    {
        for (unsigned long int j = 0; j < k; j++)
        {
            std::cin >> value;
            buffer[j] = value;
        }
        window.AnalyseFirstKMinElements(buffer);
    }
    
    buffer.clear();
    if (n % k != 0)
    {
        for (unsigned long int j = 0; j < n % k; j++)
        {
            std::cin >> value;
            buffer.push_back(value);
        }
        window.AnalyseFirstKMinElements(buffer);
    }
    
    window.PrintWindow();
    
    return 0;
}
