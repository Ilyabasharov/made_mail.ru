//
//  Parser realisation
//
//  parser.hpp
//  String Parser with callback functions
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <vector>
#include <functional>

using FunctionForString = std::function<void(const std::string &x)>;
using FunctionForNumber = std::function<void(float x)>;
using FunctionForEnds = std::function<void(void)>;

class Parser
{
private:
    std::vector <FunctionForString> string_functions;
    std::vector <FunctionForNumber> number_functions;
    std::vector<std::vector<FunctionForEnds>> ends_functions;
    const std::string string;
    std::size_t iterator;
    bool isNumber;
    
public:
    Parser(const std::string &string,
           std::vector <FunctionForString> &str,
           std::vector <FunctionForNumber> &num,
           std::vector<std::vector<FunctionForEnds>> &ends_functions);
    Parser(const std::string &string);
    ~Parser();
    
    void CallbackManager(FunctionForString& func);
    void CallbackManager(FunctionForNumber& func);
    void CallbackManager(FunctionForEnds& func, bool start);
    
    void СonsistentParser();
    std::string GetString();
};

#endif /* parser_hpp */
