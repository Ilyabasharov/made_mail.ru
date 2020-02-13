//
//  tests.hpp
//  String Parser with callback functions
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp

#include "parser.hpp"
#include <cassert>

void test(std::vector<FunctionForString> &for_string,
          std::vector<FunctionForNumber> &for_number,
          std::vector <std::vector<FunctionForEnds>> &for_ends,
          const std::string &string,
          std::vector <float> &parse_buffer,
          std::vector <float> check_buffer, bool spec_init);

void tests();

#endif /* tests_hpp */
