//
//  Dynamic Hash table with double hashing 
//
//  main.cpp
//  Hash Table
//
//  Created by Илья Башаров on 22/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "hash_table.hpp"

int main()
{
    HashTable table(8);
    char command = ' ';
    std::string value;
    
    while (std::cin >> command >> value)
    {
        switch (command)
        {
            case '?':
                std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
                
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
                
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
