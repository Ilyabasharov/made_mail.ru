//
//  Matrix class realisation
//
//  matrix.hpp
//  Matrix
//
//  Created by Илья Башаров on 05/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

class pMatrix
{
private:
    std::vector<int> &row;
    
public:
    pMatrix(std::vector<int> &row);
    ~pMatrix();
    int& operator [] (const int j);
    void operator = (const std::vector<int> &new_row);
};

class Matrix
{
private:
    std::vector<std::vector<int>> matrix;
    
public:
    Matrix(const std::vector<std::vector<int>> &vec);
    Matrix(const std::size_t rows, const std::size_t colomns, const int value = 0);
    ~Matrix();
    
    std::size_t getRows() const;
    std::size_t getColumns() const;
    
    pMatrix operator [] (const int i);
    
    Matrix operator * (const int value) const;
    Matrix operator * (const Matrix& other) const;
    Matrix& operator *= (const int value);
    Matrix& operator *= (const Matrix& other);
    
    friend bool operator == (const Matrix& left, const Matrix& right);
    friend bool operator == (const Matrix& left, const std::vector<std::vector<int>> &vec);
    friend bool operator != (const Matrix& left, const Matrix& right);
    friend std::ostream& operator << (std::ostream& out, const Matrix& matrix);
};

#endif /* matrix_hpp */
