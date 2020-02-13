//
//  splay_tree.hpp
//  Splay Tree
//
//  Created by Илья Башаров on 14/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef splay_tree_hpp
#define splay_tree_hpp

#include <iostream>

struct SplayNode
{
    unsigned long int key = 0;
    unsigned long int statistic = 1;
    SplayNode* left = nullptr;
    SplayNode* right = nullptr;
}typedef SplayNode, *pSplayNode;

class SplayTree
{
private:
    pSplayNode root;
    
public:
    SplayTree();
    explicit SplayTree(pSplayNode root);
    ~SplayTree();
    
    SplayTree(const SplayTree&) = delete;
    SplayTree(SplayTree&&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;
    SplayTree& operator=(SplayTree&&) = delete;
    
    void insert(unsigned long int);
    void erase(unsigned long int);
    bool find(unsigned long int);
    long int getKStatistic(unsigned long int);
    void printPreOrder();
    void createGraph();
    
private:
    void fixCount(pSplayNode);
    unsigned long int countStat(pSplayNode);
    
    pSplayNode leftRotate(pSplayNode);
    pSplayNode rightRotate(pSplayNode);
    pSplayNode splay_(pSplayNode, unsigned long int);
    void printPreOrder_(pSplayNode);
    long int getKStatistic_(pSplayNode,
                            unsigned long int);
    
    void splay(unsigned long int);
    void buildGraphWithGraphViz(FILE* fp, pSplayNode node);
};



#endif /* splay_tree_hpp */
