//
//  splay_tree.cpp
//  Splay Tree
//
//  Created by Илья Башаров on 14/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "splay_tree.hpp"

SplayTree::SplayTree():
root(nullptr)
{}

SplayTree::SplayTree(pSplayNode root):
root(root)
{}

SplayTree::~SplayTree()
{
    if (!root)
        return;
    
    if (root -> left)
        delete root -> left;
    
    if (root -> right)
        delete root -> right;
    
    delete root;
}

/* rightRotate:
 
       node               new_node
       /   \                /   \
  new_node  Z     ==>      X    node
  /      \                      /  \
 X        Y                    Y    Z
*/

pSplayNode SplayTree::rightRotate(pSplayNode node)
{
    pSplayNode new_node = node -> left;
    node -> left = new_node -> right;
    new_node -> right = node;
    
    fixCount(new_node -> right);
    fixCount(new_node);
    
    return new_node;
}

/* leftRotate:
 
      node                    new_node
      /  \                     /    \
     X  new_node    ==>      node    Z
        /      \             /    \
       Y        Z           X      Y
*/

pSplayNode SplayTree::leftRotate(pSplayNode node)
{
    pSplayNode new_node = node -> right;
    node -> right = new_node -> left;
    new_node -> left = node;
    
    fixCount(new_node -> left);
    fixCount(new_node);
    
    return new_node;
}

pSplayNode SplayTree::splay_(pSplayNode node, unsigned long int key)
{
    if (!node || node -> key == key)
        return node;
    
    if (node -> key > key)
    {
        if (!node -> left)
            return node;
        
        // Zig-Zig (Left Left)
        if (node -> left -> key > key)
        {
            node -> left -> left = splay_(node -> left -> left, key);
            node = rightRotate(node);
        }
        // Zig-Zag (Left Right)
        else if (node -> left -> key < key)
        {
          node -> left -> right = splay_(node -> left -> right, key);

          if (node -> left -> right)
              node -> left = leftRotate(node -> left);
        }
        
        return node -> left ? rightRotate(node) : node;
    }
    else
    {
        if (!node -> right)
            return node;

        // Zag-Zig (Right Left)
        if (node -> right -> key > key)
        {
            node -> right -> left = splay_(node -> right -> left, key);
            if (node -> right -> left)
                node -> right = rightRotate(node -> right);
        }
        //Zag-Zag (Right Right)
        else if (node -> right -> key < key)
        {
              node -> right -> right = splay_(node -> right -> right, key);
              node = leftRotate(node);
        }

        return node -> right ? leftRotate(node) : node;
    }
}

void SplayTree::splay(unsigned long int key)
{
    root = splay_(root, key);
}

void SplayTree::erase(unsigned long int key)
{
    splay(key);
    
    if (!root || key != root -> key)
        return;
    
    pSplayNode temp = root;
    
    if (!root -> left)
        root = root -> right;
    else
    {
        root = splay_(root -> left, key);
        root -> right = temp -> right;
        fixCount(root);
    }
    
    delete temp;
}

void SplayTree::fixCount(pSplayNode node)
{
    if (node)
        node -> statistic = countStat(node -> left)
            + countStat(node -> right) + 1;
}

unsigned long int SplayTree::countStat(pSplayNode node)
{
    return node ? node -> statistic : 0;
}

bool SplayTree::find(unsigned long int key)
{
    return splay_(root, key) ? true : false;
}

void SplayTree::insert(unsigned long int key)
{
    if (!root)
    {
        root = new SplayNode{key};
        return;
    }
  
    splay(key);
  
    pSplayNode newnode = new SplayNode{key};
  
    if (root -> key > key)
    {
        
        newnode -> right = root;
        newnode -> left = root -> left;
        root -> left = nullptr;
        
        fixCount(newnode -> right);
    }
    else
    {
        newnode -> left = root;
        newnode -> right = root -> right;
        root -> right = nullptr;
        
        fixCount(newnode -> left);
    }
    
    fixCount(newnode);
  
    root = newnode;
}

void SplayTree::printPreOrder_(pSplayNode node)
{
    if (!node)
        return;
    
    std::cout << "Key: " << node -> key << " Stat: " << node -> statistic << ' ' << std::endl;
    
    if (node -> left)
        printPreOrder_(node -> left);
        
    if (node -> right)
        printPreOrder_(node -> right);
}

void SplayTree::printPreOrder()
{
    printPreOrder_(root);
}

long int SplayTree::getKStatistic(unsigned long int stat)
{
    return getKStatistic_(root, stat);
}

long int SplayTree::getKStatistic_(pSplayNode node,
                       unsigned long int stat)
{
    
    if (!node || node -> statistic < stat || stat < 0)
        return -1;
    
    pSplayNode current = node;
    
    while (current)
    {
        if (countStat(current -> left) == stat)
            return current -> key;
        
        else if (countStat(current -> left) > stat)
            current = current -> left;
        
        else
        {
            stat = stat - countStat(current -> left) - 1;
            current = current -> right;
        }
    }
    
    return -1;
}

void SplayTree::buildGraphWithGraphViz(FILE* fp, pSplayNode node)
{
    fprintf(fp, "TreeNode_%p [label=\"stat=%lu, %lu\\l\"]\n", node,
            node -> statistic, node -> key);
    
    if (node -> left)
    {
        buildGraphWithGraphViz(fp, node -> left);
        fprintf(fp, "TreeNode_%p -> TreeNode_%p\n", node, node -> left);
        fprintf(fp, "TreeNode_%p [label=\"stat=%lu, %lu\\l\"]\n", node, node -> statistic, node -> key);
    }
    
    if (node -> right)
    {
        buildGraphWithGraphViz(fp, node -> right);
        fprintf(fp, "TreeNode_%p -> TreeNode_%p\n", node, node -> right);
        fprintf(fp, "TreeNode_%p [label=\"stat=%lu, %lu\\l\"]\n", node,
                node -> statistic, node -> key);
    }
}

void SplayTree::createGraph()
{
    FILE *dotFile = fopen("graph.gv", "w");
    
    fprintf(dotFile, "digraph G{\ngraph [dpi = 300]");
    buildGraphWithGraphViz(dotFile, root);
    fprintf(dotFile, "}");
    fclose(dotFile);
}
