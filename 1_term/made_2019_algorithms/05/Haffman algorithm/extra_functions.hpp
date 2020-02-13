//
//  extra_functions.hpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 10/12/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef extra_functions_hpp
#define extra_functions_hpp

#include <unordered_map>
#include "stream.hpp"
#include "binary_tree.hpp"

inline void Traversal(pBinaryNode root, std::vector<bool>& buffer,
               std::unordered_map<std::vector<bool>, byte>* map_vec_byte = nullptr,
               std::unordered_map<byte, std::vector<bool>>* map_byte_vec = nullptr)
{
    if (root -> right)
    {
        buffer.push_back(true);
        Traversal(root -> right, buffer, map_vec_byte, map_byte_vec);
        buffer.pop_back();
    }
    
    if (root -> left)
    {
        buffer.push_back(false);
        Traversal(root -> left, buffer, map_vec_byte, map_byte_vec);
        buffer.pop_back();
    }
    
    if (!root -> right && !root -> left)
    {
        
        if (map_vec_byte)
            (*map_vec_byte)[buffer] = root -> key;
        else
            (*map_byte_vec)[root -> key] = buffer;
    }
}

inline std::size_t MaxValueElement(std::unordered_map<byte, std::size_t>& map)
{
    std::size_t max = map.begin() -> second;
    
    for (auto iterator = ++map.begin(); iterator != map.end(); iterator++)
        if (iterator -> second > max)
            max = iterator -> second;
    
    return max;
}

inline std::vector<std::pair<byte, std::size_t>> CountingSort(std::unordered_map<byte,
                                                       std::size_t>& map)
{
    if (map.empty())
        throw std::invalid_argument{"Alphabet is empty."};
    
    std::vector<std::vector<std::pair<byte, std::size_t>>> buffer(MaxValueElement(map));
    
    for (auto& iterator : map)
        buffer[iterator.second - 1].push_back(std::move(iterator));
    
    std::vector<std::pair<byte, std::size_t>> result(map.size());
    
    std::size_t iterator = 0;
    
    for (auto& local_buffers : buffer)
        for (auto& element : local_buffers)
            result[iterator++] = std::move(element);
    
    return result;
}

#endif /* extra_functions_hpp */
