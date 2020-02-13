//
//  big_int.hpp
//  BigInt
//
//  Created by Илья Башаров on 18/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef big_int_hpp
#define big_int_hpp

#include "extra_functions.hpp"

class BigInt
{
private:
    char* number;
    std::size_t size;
    bool sign;
    
    BigInt(char* value, std::size_t size, bool sign);
    
public:
    ~BigInt();
    BigInt();
    
    BigInt(int a);
    BigInt(const BigInt& copied);
    BigInt(BigInt&& moved);
    BigInt(const std::string& string);
    
    friend std::ostream& operator << (std::ostream& out, const BigInt& number);
    friend std::istream& operator >> (std::istream& in, BigInt& number);
    
    friend const bool operator < (const BigInt &num1, const BigInt &num2);
    friend const bool operator < (const BigInt &num1, const int& num2);
    friend const bool operator < (const int& num1, const BigInt &num2);
    
    friend const bool operator > (const BigInt &num1, const BigInt &num2);
    friend const bool operator > (const BigInt &num1, const BigInt &num2);
    friend const bool operator > (const int& num1, const BigInt &num2);
    
    friend const bool operator <= (const BigInt &num1, const BigInt &num2);
    friend const bool operator <= (const BigInt &num1, const int &num2);
    friend const bool operator <= (const int& num1, const BigInt &num2);
    
    friend const bool operator >= (const BigInt &num1, const BigInt &num2);
    friend const bool operator >= (const BigInt &num1, const int &num2);
    friend const bool operator >= (const int& num1, const BigInt &num2);
    
    friend const bool operator != (const BigInt &num1, const BigInt &num2);
    friend const bool operator != (const BigInt &num1, const int &num2);
    friend const bool operator != (const int& num1, const BigInt &num2);
    
    friend const bool operator == (const BigInt &num1, const BigInt &num2);
    friend const bool operator == (const BigInt &num1, const int &num2);
    friend const bool operator == (const int& num1, const BigInt &num2);
    
    friend const BigInt operator + (const BigInt& value);
    friend const BigInt operator + (const BigInt &num1, const BigInt &num2);
    friend const BigInt operator + (const BigInt &num1, const int &num2);
    friend const BigInt operator + (const int& num1, const BigInt &num2);
    
    friend const BigInt operator - (const BigInt& value);
    friend const BigInt operator - (const BigInt &num1, const BigInt &num2);
    friend const BigInt operator - (const BigInt &num1, const int &num2);
    friend const BigInt operator - (const int& num1, const BigInt &num2);
};

#endif /* big_int_hpp */
