//
//  binary_tree.cpp
//  Binary tree with pre-order
//
//  Created by Илья Башаров on 13/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "binary_tree.hpp"

void iterativePreOrder(pNode root)
{
    if (root == nullptr)
        return;
    
    std::vector<pNode> nodeStack;
    nodeStack.push_back(root);
    
    while (!nodeStack.empty())
    {
        pNode node = nodeStack.back();
        nodeStack.pop_back();
        std::cout << node -> key << ' ';;
        
        if (node -> left)
            nodeStack.push_back(node -> left);
        
        if (node -> right)
            nodeStack.push_back(node -> right);
    }
    
    std::cout << std::endl;
}

void addNode(pNode root, long long int key)
{
    pNode current_root = nullptr, next = root;
    
    do
    {
        std::swap(next, current_root);
        next = current_root -> key > key ?
            current_root -> right :
            current_root -> left;
    }
    while (next);

    current_root -> key > key ?
        current_root -> right = new Node{key} :
        current_root -> left = new Node{key};
}

void free_tree(pNode root)
{
    if (root == nullptr)
        return;
    
    std::vector<pNode> nodeStack;
    nodeStack.push_back(root);
    
    std::vector<pNode> deleteStack;
    
    while (!nodeStack.empty())
    {
        pNode node = nodeStack.back();
        nodeStack.pop_back();
        
        deleteStack.push_back(node);
        
        if (node -> left)
            nodeStack.push_back(node -> left);
        
        if (node -> right)
            nodeStack.push_back(node -> right);
    }
    
    while (!deleteStack.empty())
    {
        delete deleteStack.back();
        deleteStack.pop_back();
    }
}
