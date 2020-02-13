//
//  Dynamic Hash table with double hashing realisation
//
//  hash_table.cpp
//  Hash Table
//
//  Created by Илья Башаров on 22/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "hash_table.hpp"

HashTable::HashTable (std::size_t initial_size):
table(std::vector<HashTableNode>(initial_size, HashTableNode())),
capacity(0), tableSize(initial_size)
{}

bool HashTable::Has_(const std::string& key, std::size_t& external_hash) const
{
    std::size_t h1 = hash1(key) % tableSize, h2 = hash2(key),
                i = 1, currentHash = h1;
    
    while(!table[currentHash].isEmpty && i < tableSize)
    {
        if(table[currentHash].key == key && !table[currentHash].isDeleted)
        {
            external_hash = currentHash;
            return true;
        }
        
        currentHash = hash_func(h1, h2, tableSize, i++);
    }
    
    return false;
}

bool HashTable::Has (const std::string& key) const
{
    std::size_t external_hash = 0;
    return Has_(key, external_hash);
}

bool HashTable::Add (const std::string& key)
{
    if (4*capacity >= 3*tableSize)
        Rehashing();
    
    std::size_t h1 = hash1(key) % tableSize, h2 = hash2(key),
                i = 1, currentHash = h1, indexDeleted = tableSize;
    
    while(!table[currentHash].isEmpty && i < tableSize)
    {
        if(table[currentHash].key == key && !table[currentHash].isDeleted)
            return false;
        
        if(table[currentHash].isDeleted && indexDeleted == tableSize)
            indexDeleted = currentHash;
        
        currentHash = hash_func(h1, h2, tableSize, i++);
    }
    
    if (indexDeleted != tableSize)
    {
        table[indexDeleted].key = key;
        table[indexDeleted].isDeleted = false;
    }
    else
        table[currentHash] = HashTableNode(key);
    
    capacity++;
    return true;
}

bool HashTable::Remove (const std::string& key)
{
    std::size_t hash = 0;
    bool result = Has_(key, hash);
    
    if (result)
    {
        table[hash].isDeleted = true;
        capacity --;
    }
    
    return result;
}

void HashTable::Rehashing ()
{
    std::size_t new_size = 2*table.size();
    
    std::vector<HashTableNode> new_table(new_size, HashTableNode());
    
    for (std::size_t i = 0; i < tableSize; i++)
    {
        if (!table[i].isEmpty && !table[i].isDeleted)
        {
            std::size_t h1 = hash1(table[i].key) % new_size,
                        h2 = hash2(table[i].key),
                        j = 1,
                        current_hash = h1;
            
            while(!new_table[current_hash].isEmpty && j < new_size)
                current_hash = hash_func(h1, h2, new_size, j++);
            
            new_table[current_hash] = HashTableNode(table[i].key);
        }
        
        table[i].isEmpty = false;
    }
    
    new_table.swap(table);
    tableSize = new_size;
}
