//
//  binary_tree.hpp
//  Binary tree with pre-order
//
//  Created by Илья Башаров on 13/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef binary_tree_hpp
#define binary_tree_hpp

#include <iostream>
#include <vector>

struct Node
{
    long long int key;
    Node* left = nullptr;
    Node* right = nullptr;
}typedef Node,  *pNode;

pNode newNode(long long int key);
void iterativePreOrder(pNode root);
void addNode(pNode root, long long int key);
void free_tree(pNode root);

#endif /* binary_tree_hpp */
