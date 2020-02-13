//
//  main.cpp
//  Splay Tree
//
//  Created by Илья Башаров on 14/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "splay_tree.hpp"

int main()
{
    unsigned long int N;
    long int value1, value2;
    
    std::cin >> N;
    SplayTree tree;
    
    for (unsigned long int i = 0; i < N; ++i)
    {
        std::cin >> value1 >> value2;
        
        if (value1 >= 0)
        {
            tree.insert(value1);
            std::cout << tree.getKStatistic(value2) << std::endl;
            //tree.createGraph();
        }
        else
        {
            tree.erase(-value1);
            std::cout << tree.getKStatistic(value2) << std::endl;
            //tree.createGraph();
        }
    }
    
    return 0;
}
