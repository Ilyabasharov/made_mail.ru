//
//  extra_functions.hpp
//  BigInt
//
//  Created by Илья Башаров on 25/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef extra_functions_hpp
#define extra_functions_hpp

#include <iostream>
#include <string>
#include <cstring>

char* isInteger(const std::string& string, bool& sign, std::size_t& size);
char* leftNumberAddition(char* result, std::size_t result_length,
                       std::size_t expected_length, char number);
char* myStrDup(char* string, std::size_t length);
char* zerosDeleting(char* string, std::size_t& length);

#endif /* extra_functions_hpp */
