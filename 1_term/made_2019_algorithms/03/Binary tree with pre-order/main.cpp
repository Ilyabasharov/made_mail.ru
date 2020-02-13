//
//  Non-recursive binary tree pre-order traversal realisation
//
//  main.cpp
//  Binary tree with pre-order
//
//  Created by Илья Башаров on 13/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "binary_tree.hpp"

int main()
{
    unsigned long long int N = 0;
    std::cin >> N;
    
    if (N < 1)
        return 0;
    
    long long int value = 0;
    std::cin >> value;
    
    pNode tree = new Node{value};
    
    for (unsigned long long int i = 1; i < N; ++i)
    {
        std::cin >> value;
        addNode(tree, value);
    }
    
    iterativePreOrder(tree);
    free_tree(tree);
    
    return 0;
}
