//
//  extra_functions.cpp
//  BigInt
//
//  Created by Илья Башаров on 25/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "extra_functions.hpp"

/* Only removing zeros at the beginning of a line */
char* zerosDeleting(char* string, std::size_t& length)
{
    std::size_t i = 0;
    for (; i < length; ++i)
        if (string[i] != '0')
            break;
    
    char* result = new char[length - i];
    std::copy(string + i, string + length, result);
    length = length - i;
    
    return result;
}

/* Hand-made variant of StrDup */
char* myStrDup(char* string, std::size_t length)
{
    char* new_str = new char[length];
    std::copy(string, string + length, new_str);
    
    return new_str;
}

/* Complement the line on the left with numbers equal to number variable,
 final length will be expected_length  */
char* leftNumberAddition(char* result, std::size_t difference,
                       std::size_t expected_length, char number)
{
    char* tmp = new char[expected_length];
    for (std::size_t i = 0; i < expected_length; ++i)
        tmp[i] = i < difference ? number : result[i - difference];
    
    return tmp;
}

/* Checking string as Integer,
 removing all zeros at the beginning */

char* isInteger(const std::string& string, bool& sign, std::size_t& size)
{
    if (string.length() == 0)
        return nullptr;
    
    sign = string[0] == '-' ? true : false;
    
    std::size_t i = sign;
    for (; i < string.length(); ++i)
    {
        if (isdigit(string[i]))
        {
            if (string[i] != '0')
                break;
        }
        else
            return nullptr;
    }
    
    if (i == string.length())
    {
        sign = false; size = 1;
        return new char[1]{'0'};
    }
    
    std::size_t start = i;
    char* result = new char[string.length() - i];
    
    for (; i < string.length(); ++i)
    {
        if (isdigit(string[i]))
            result[i - start] = string[i];
        else
            return nullptr;
    }
    size = string.length() - start;
    return result;
}
