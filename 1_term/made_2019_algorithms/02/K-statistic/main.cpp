//
//  The program finds k-statistic element in offered buffer.
//  Time complexity is O(n) in average, O (n^2) in worst case.
//
//  main.cpp
//  K-statistic
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "quick_select.hpp"

int main()
{
    unsigned int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> buffer(n);
    for (unsigned int i = 0; i < n; i ++)
        std::cin >> buffer[i];
    
    std::cout << QuickSelect(buffer, k) << std::endl;
    
    return 0;
}
