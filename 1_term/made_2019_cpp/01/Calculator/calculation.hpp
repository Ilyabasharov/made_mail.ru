//
//  Recursive descent parser main class
//
//  calculation.hpp
//  Calculator
//
//  Created by Илья Башаров on 15/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef calculation_hpp
#define calculation_hpp

#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

const int ERROR_CODE = 1;

class DescentParser
{
public:
    
    std::string expression;
    std::string::iterator cursor;
    bool user_error = false;
    
    int RecursiveDescentParser();
    int GetNumber();
    int GetAdditionOrSubtraction();
    int GetMultiplyingOrDivision();
    int GetPriority();
    int GetUnaryMinusOrPlus();
    void Update(const char *tmp_string);
    
    DescentParser(const char *tmp_string);
    ~DescentParser();
};

bool isBackspacing(const char* string);
#endif /* calculation_hpp */
