//
//  hash_func.cpp
//  Hash Table
//
//  Created by Илья Башаров on 22/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "hash_func.hpp"

std::size_t hash1 (const std::string &key)
{
    std::size_t hash = 0;
    for (auto& symbol: key)
        hash = hash*11 + symbol;
    
    return hash;
}

std::size_t hash2 (const std::string &key)
{
    return key.size() > 1 ?
           (key[0] + key[key.size() - 1])*2 + 1 :
            1;
}

std::size_t hash_func (const std::size_t hash1,
                       const std::size_t hash2,
                       const std::size_t size,
                       const std::size_t iterator)
{
    return (hash1 + iterator*hash2) % size;
}
