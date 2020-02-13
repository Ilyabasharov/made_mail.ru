//
//  hash_table.hpp
//  Hash Table
//
//  Created by Илья Башаров on 22/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef hash_table_hpp
#define hash_table_hpp

#include <vector>
#include "hash_func.hpp"

class HashTable
{
private:
    struct HashTableNode
    {
        std::string key;
        bool isDeleted, isEmpty;
        
        explicit HashTableNode(const std::string& key):
            key(key), isDeleted(false), isEmpty(false) {}
        
        HashTableNode():
            isDeleted(false), isEmpty(true) {}
    }typedef HashTableNode;
    
    std::vector<HashTableNode> table;
    std::size_t capacity, tableSize;
    bool Has_(const std::string&, std::size_t&) const;
    void Rehashing();

public:
    explicit HashTable(std::size_t);
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;
    
    bool Remove(const std::string&);
    bool Add(const std::string&);
    bool Has(const std::string&) const;
};

#endif /* hash_table_hpp */
