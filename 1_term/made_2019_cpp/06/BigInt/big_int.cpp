//
//  big_int.cpp
//  BigInt
//
//  Created by Илья Башаров on 18/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "big_int.hpp"

BigInt::~BigInt()
{
    delete [] number;
    number = nullptr;
    size = 0;
}

BigInt::BigInt():
number(new char[1]{'0'}),
size(1),
sign(false)
{}

BigInt::BigInt(char* value, std::size_t size, bool sign):
number(value), size(size), sign(sign)
{}

BigInt::BigInt(const BigInt& copied):
number(new char[copied.size]), size(copied.size),
sign(copied.sign)
{
    std::copy(copied.number, copied.number + size, number);
}

BigInt::BigInt(BigInt&& moved):
number(moved.number),
size(moved.size),
sign(moved.sign)
{
    moved.number = nullptr;
    moved.size = 0;
    moved.sign = 0;
}

BigInt::BigInt(const std::string& string):
number(isInteger(string, sign, size))
{
    if (!number)
        throw std::domain_error("Invalid string to constructor.");
}

BigInt::BigInt(int a):
sign(a < 0 ? true : false)
{
    std::string tmp = std::to_string(std::abs(a));
    size = tmp.length();
    number = new char[size];
    std::copy(tmp.c_str(), tmp.c_str() + size, number);
}

std::ostream& operator << (std::ostream& out, const BigInt& number)
{
    if (number.sign)
        out << '-';
    
    for (unsigned int i = 0; i < number.size; ++i)
        out << number.number[i];
    
    return out;
}

std::istream& operator >> (std::istream& in, BigInt& number)
{
    
    std::string current;
    in >> current;
    number.number = isInteger(current,
                              number.sign, number.size);
    if (!number.number)
        throw std::domain_error("Invalid string to operator >>.");
        
    return in;
}

const bool operator < (const BigInt &num1, const BigInt &num2)
{
    if (num1.sign)
        if (num2.sign)
        {
            if (num2.size < num1.size)
                return true;
            else if (num2.size > num1.size)
                return false;
            else
                return strncmp(num1.number, num2.number, num1.size) > 0;
        }
        else
            return true;
    else
        if (num2.sign)
            return false;
        else
        {
            if (num2.size > num1.size)
                return true;
            else if (num2.size < num1.size)
                return false;
            else
                return strncmp(num1.number, num2.number, num1.size) < 0;
        }
}

const bool operator < (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 < right;
}

const bool operator < (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left < num2;
}

const bool operator > (const BigInt &num1, const BigInt &num2)
{
    return num2 < num1;
}

const bool operator > (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 > right;
}

const bool operator > (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left > num2;
}

const bool operator <= (const BigInt &num1, const BigInt &num2)
{
    return !(num2 < num1);
}

const bool operator <= (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 <= right;
}

const bool operator <= (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left <= num2;
}

const bool operator >= (const BigInt &num1, const BigInt &num2)
{
    return !(num1 < num2);
}

const bool operator >= (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 >= right;
}

const bool operator >= (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left >= num2;
}

const bool operator == (const BigInt &num1, const BigInt &num2)
{
    if (num1.sign != num2.sign || num1.size != num2.size ||
        strncmp(num1.number, num2.number, num1.size) != 0)
        return false;
    
    return true;
}

const bool operator == (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 == right;
}

const bool operator == (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left == num2;
}

const bool operator != (const BigInt &num1, const BigInt &num2)
{
    return !(num1 == num2);
}

const bool operator != (const BigInt &num1, const int& num2)
{
    BigInt right(num2);
    
    return num1 != right;
}

const bool operator != (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left != num2;
}

const BigInt operator + (const BigInt& value)
{
    return BigInt(value);
}

const BigInt operator + (const BigInt &num1, const BigInt &num2)
{
    if (num1.sign == num2.sign)
    {
        long int difference = num1.size - num2.size;
        char* term1 = difference >= 0 ?
            leftNumberAddition(num2.number, difference, num1.size, '0') :
            leftNumberAddition(num1.number, -difference, num2.size, '0');
        char* term2 = difference >= 0 ? num1.number : num2.number;
        std::size_t size = difference >= 0 ? num1.size : num2.size;
        
        bool transfer = false;
        
        for (long int i = size - 1; i >= 0; --i)
        {
            char temp = term1[i] + term2[i] - 2*'0' + transfer;
            transfer = temp > 9 ? true : false;
            term1[i] = transfer ? temp - 10 + '0' : temp + '0';
        }
        
        char* result = term1;
        if (transfer)
        {
            result = leftNumberAddition(term1, 1, size + 1, '1');
            size = size + 1;
            delete [] term1;
        }
        
        return BigInt{result, size, num1.sign};
    }
    else
    {
        if (num2.sign)
            return num1 - (-num2);
        else
            return num2 - (-num1);
    }
}

const BigInt operator + (const BigInt &num1, const int &num2)
{
    BigInt right(num2);
    
    return num1 + right;
}

const BigInt operator + (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left + num2;
}

const BigInt operator - (const BigInt& value)
{
    bool sign = value.sign;
    
    if (value.number[0] != '0')
        sign = !sign;
    
    char* result = new char[value.size];
    std::copy(value.number, value.number + value.size, result);
    
    return BigInt{result, value.size, sign};
}

const BigInt operator - (const BigInt &num1, const BigInt &num2)
{
    if (num1.sign != num2.sign)// когда разных знаков - сумма
        return -num2 + num1;
    else
    {
        if (num1.sign)// когда оба отрицательных то разность
            return -num2 - (-num1);
        else // num1 - num2
        {
            
            long int difference = num1.size - num2.size;
            char* term1 = nullptr, *term2 = nullptr;
            std::size_t size = num1.size;
            bool sign = true, transfer = false;
            
            if (difference > 0)
            {
                term2 = leftNumberAddition(num2.number, difference, num1.size, '0');
                term1 = myStrDup(num1.number, num1.size);
                sign = false;
            }
            else if (difference < 0)
            {
                size = num2.size;
                term2 = leftNumberAddition(num1.number, -difference, num2.size, '0');
                term1 = myStrDup(num2.number, num2.size);
            }
            else
            {
                int compare = strncmp(num1.number, num2.number, size);
                
                if (compare == 0)
                    return BigInt();
                else if (compare > 0)
                {
                    sign = false;
                    term1 = myStrDup(num1.number, size);
                    term2 = myStrDup(num2.number, size);
                }
                else
                {
                    term1 = myStrDup(num2.number, size);
                    term2 = myStrDup(num1.number, size);
                }
            }
            for (long int i = size - 1; i >= 0; --i)
            {
                signed char temp = term1[i] - term2[i];
                transfer = (temp < 0) ? true : false;
                if (transfer)
                {
                    long int iter = i;
                    while (iter >= 0)
                    {
                        if (term1[iter] > '0')
                        {
                            term1[iter] -= 1;
                            break;
                        }
                        iter -= 1;
                    }
                    iter += 1;
                    while (iter < i)
                    {
                        term1[iter] += 9;
                        iter ++;
                    }
                    term1[iter] += 10;
                }
                term2[i] = term1[i] - term2[i] + '0';
            }
            
            delete [] term1;
            char* result = term2;
            
            if (term2[0] == '0')
            {
                result = zerosDeleting(term2, size);
                delete [] term2;
            }
            
            return BigInt{result, size, sign};
        }
    }
}

const BigInt operator - (const BigInt &num1, const int &num2)
{
    BigInt right(num2);
    
    return num1 - right;
}

const BigInt operator - (const int& num1, const BigInt &num2)
{
    BigInt left(num1);
    
    return left - num2;
}
