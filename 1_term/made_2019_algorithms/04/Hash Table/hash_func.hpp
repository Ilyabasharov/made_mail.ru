//
//  Available hash functions
//
//  hash_func.hpp
//  Hash Table
//
//  Created by Илья Башаров on 22/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef hash_func_hpp
#define hash_func_hpp

#include <iostream>
#include <string>

std::size_t hash1 (const std::string&);
std::size_t hash2 (const std::string&);

std::size_t hash_func (const std::size_t,
                       const std::size_t,
                       const std::size_t,
                       const std::size_t);

#endif /* hash_func_hpp */
