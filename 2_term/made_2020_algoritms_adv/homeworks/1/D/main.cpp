//
//  main.cpp
//  D task
//
//  Created by Илья Башаров on 29.02.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::size_t LivenstainDistance(std::string &s1, std::string &s2)
{
    std::vector<std::vector<std::size_t>> D(2, std::vector<std::size_t>(s2.size() + 1, 0));
    
    for (std::size_t j = 1; j < s2.size() + 1; j ++)
        D[0][j] = j;
    
    for (std::size_t i = 1; i < s1.size() + 1; i ++)
    {
        D[1][0] = i;
        for (std::size_t j = 1; j < s2.size() + 1; j ++)
            D[1][j] = std::min({D[1][j - 1] + 1,
                                D[0][j] + 1,
                                D[0][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});
        
        std::swap(D[0], D[1]);
    }
    
    return D[0][s2.size()];
}

int main()
{
    std::string s1, s2;
    
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);
    
    std::cout << LivenstainDistance(s1, s2) << std::endl;
    
    return 0;
}
