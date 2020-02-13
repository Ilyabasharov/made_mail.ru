//
//  Recursive descent parser functions realisation
//
//  calculation.cpp
//  Calculator
//
//  Created by Илья Башаров on 15/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "calculation.hpp"

DescentParser::DescentParser(const char *tmp_string)
{
    expression = std::string(tmp_string);
    cursor = expression.begin();
}

DescentParser::~DescentParser()
{}

int DescentParser::RecursiveDescentParser()
{
    int head = GetAdditionOrSubtraction();
    while (*cursor == ' ')
        cursor++;
    if (cursor != expression.end())
    {
        user_error = true;
        cursor = expression.end();
    }
    return head;
}

int DescentParser::GetNumber()
{
    while (*cursor == ' ')
        cursor++;
        
    if (!isdigit(*cursor))
    {
        user_error = true;
        cursor = expression.end();
    }
    
    int value1 = 0;
    
    while (isdigit(*cursor))
    {
        value1 = value1 * 10;
        value1 = value1 + *cursor - '0';
        cursor ++;
    }
    return value1;
}

int DescentParser::GetAdditionOrSubtraction()
{
    bool addition = true;
    double value1 = GetMultiplyingOrDivision();
    
    while (*cursor == ' ')
        cursor++;
    
    while (*cursor == '+' || *cursor == '-')
    {
        addition = (*cursor == '+');
        cursor++;
        
        int value2 = GetMultiplyingOrDivision();
        if (addition) value1 += value2;
        else value1 -= value2;
        
        while (*cursor == ' ')
            cursor++;
    }
    return value1;
}

int DescentParser::GetMultiplyingOrDivision()
{
    int value1 = GetPriority();
    bool multiplying = true;
    
    while (*cursor == ' ')
        cursor++;
    
    while (*cursor == '*' || *cursor == '/')
    {
        multiplying = (*cursor++ == '*');
        
        int value2 = GetPriority();
        if (multiplying)
            value1 *= value2;
        else if (value2 != 0)
                value1 /= value2;
            else
            {
                user_error = true;
                cursor = expression.end();
            }
    }
    return value1;
}

int DescentParser::GetPriority()
{
    while (*cursor == ' ')
        cursor++;
    if (*cursor != '(')
        return GetUnaryMinusOrPlus();
    cursor ++;
    int value = GetAdditionOrSubtraction();
    
    while (*cursor == ' ')
        cursor++;
    
    if (*cursor != ')')
    {
        user_error = true;
        cursor = expression.end();
    }
    cursor ++ ;
    return value;
}

int DescentParser::GetUnaryMinusOrPlus()
{
    while (*cursor == ' ')
        cursor ++;
    
    if (*cursor != '-' && *cursor != '+')
        return GetNumber();
    
    if (*cursor++ == '+')
        return GetNumber();
    
    return -GetNumber();
}

void DescentParser::Update(const char* tmp_string)
{
    user_error = false;
    
    if (isBackspacing(tmp_string))
    {
        user_error = true;
        return;
    }
    
    expression = std::string(tmp_string);
    cursor = expression.begin();
}

bool isBackspacing(const char* string)
{
    for(int i = 0; i < strlen(string); i++)
        if (string[i] != ' ')
            return false;
    
    return true;
}
