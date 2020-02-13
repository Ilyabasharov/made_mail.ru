//
//  Parser realisation
//
//  parser.cpp
//  String Parser with callback functions
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "parser.hpp"

Parser::Parser(const std::string &string,
               std::vector <FunctionForString> &str,
               std::vector <FunctionForNumber> &num,
               std::vector<std::vector<FunctionForEnds>> &ends_functions):
string_functions(str), number_functions(num),
ends_functions(ends_functions), string(string),
iterator(0), isNumber(false)
{}

Parser::Parser(const std::string &string):
ends_functions(std::vector<std::vector<FunctionForEnds>>(2)),
string(string), iterator(0), isNumber(false)
{}

Parser::~Parser()
{}

void Parser::СonsistentParser()
{
    for (auto &function_start : ends_functions[0])
        function_start();
    
    while (iterator < string.length())
    {
        std::string current_string = GetString();
        
        if (current_string.length() == 0)
            continue;
            
        if (isNumber)
        {
            for (auto &function : number_functions)
                function(std::stof(current_string, nullptr));
        }
        else
            for (auto &function : string_functions)
                function(current_string);
    }
    
    for (auto &function_end : ends_functions[1])
        function_end();
}

std::string Parser::GetString()
{
    isNumber = true;
    std::string current_string;
    int point_count = 0;
    std::size_t start_point = 0;
    
    while (string[iterator] == ' ' && iterator < string.length())
        iterator++;
    
    if (string[iterator] == '-')
    {
        current_string.push_back(string[iterator]);
        iterator++;
    }
    
    start_point = iterator;
    
    while (string[iterator] != ' ' && iterator < string.length())
    {
        if (isdigit(string[iterator]) || (string[iterator] == '.' && start_point < iterator))
        {
            if (string[iterator] == '.' && start_point < iterator)
                point_count += 1;
            
        }
        else
            isNumber = false;
        
        current_string.push_back(string[iterator]);
        iterator++;
    }
    
    if (point_count > 1)
        isNumber = false;
    
    return current_string;
}

void Parser::CallbackManager(FunctionForString &func)
{
    string_functions.push_back(func);
}

void Parser::CallbackManager(FunctionForNumber &func)
{
    number_functions.push_back(func);
}

void Parser::CallbackManager(FunctionForEnds &func, bool start)
{
    ends_functions[start].push_back(func);
}
