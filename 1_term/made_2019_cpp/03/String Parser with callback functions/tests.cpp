//
//  Test system
//
//  tests.cpp
//  String Parser with callback functions
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "tests.hpp"

void test(std::vector <FunctionForString> &for_string,
          std::vector <FunctionForNumber> &for_number,
          std::vector <std::vector<FunctionForEnds>> &for_ends,
          const std::string &string, std::vector <float> &parse_buffer,
          std::vector <float> check_buffer, bool spec_init)
{
    if (spec_init)
    {
        Parser parser(string);
        
        for (auto& func : for_string)
            parser.CallbackManager(func);
        
        for (auto& func : for_number)
            parser.CallbackManager(func);
        
        for (auto& func : for_ends[0])
            parser.CallbackManager(func, false);
        
        for (auto& func : for_ends[1])
            parser.CallbackManager(func, true);
        
        parser.СonsistentParser();
        
        assert(parse_buffer == check_buffer);
        std::cout << '.';
        
        parse_buffer.clear();
        check_buffer.clear();
        return;
    }
    
    Parser parser(string, for_string, for_number, for_ends);
    
    parser.СonsistentParser();
    
    assert(parse_buffer == check_buffer);
    std::cout << '.';
    
    parse_buffer.clear();
    check_buffer.clear();
}

void tests()
{
    std::vector <float> buffer;
    std::vector <float> check_buffer;
    std::vector <FunctionForString> for_string;
    std::vector <FunctionForNumber> for_number;
    std::vector <std::vector<FunctionForEnds>> for_ends;
    
    /*---------------------------------FIRST-TEST--------------------------------*/
    for_string = std::vector <FunctionForString>
    {
        [&buffer](const std::string &a) -> void {buffer.push_back(0);},
        [&buffer](const std::string &a) -> void {buffer.push_back(5);}
    };
    
    for_number = std::vector <FunctionForNumber>
    {
        [&buffer](float a) -> void {buffer.push_back(a);},
        [&buffer](float a) -> void {buffer.push_back(a*a*a);}
        
    };
    
    for_ends.push_back({[&buffer]() -> void {buffer.push_back(10);}});
    for_ends.push_back({[&buffer]() -> void {buffer.push_back(20);}});
    
    test(for_string, for_number, for_ends, "2.0 asda", buffer, {10, 2, 8, 0, 5, 20}, false);
    
    /*--------------------------------SECOND-TEST--------------------------------*/
    test(for_string, for_number, for_ends, "-2.0 asda", buffer, {10, -2, -8, 0, 5, 20}, true);
    
    /*--------------------------------THIRD-TEST---------------------------------*/
    test(for_string, for_number, for_ends, "-9 -asda", buffer, {10, -9, -729, 0, 5, 20}, false);
    
    /*--------------------------------FOURTH-TEST--------------------------------*/
    test(for_string, for_number, for_ends, "asa   2.5 0", buffer, {10, 0, 5, 2.5, 15.625, 0, 0, 20}, true);
    
    /*--------------------------------FIFTH-TEST--------------------------------*/
    test(for_string, for_number, for_ends, "asa   2.5 0 asda3s34d 1", buffer, {10, 0, 5, 2.5, 15.625, 0, 0, 0, 5, 1, 1, 20}, true);
    /*--------------------------------------------------------------------------*/
    
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}
