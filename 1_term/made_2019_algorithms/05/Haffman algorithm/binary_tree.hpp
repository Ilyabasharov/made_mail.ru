//
//  binary_tree.hpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 12.01.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#ifndef binary_tree_h
#define binary_tree_h

#include "bits_workers.hpp"

struct BinaryNode
{
    byte key = '$';
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
    
}typedef BinaryNode, *pBinaryNode;

inline BinaryNode* MergeNodes (pBinaryNode left, BinaryNode* right)
{
    return new BinaryNode{'$', left, right};
}

inline void FreeMemory(pBinaryNode root)
{
    if (!root)
        return;
    
    FreeMemory(root -> left);
    FreeMemory(root -> right);
    delete root;
}


#endif /* binary_tree_h */
