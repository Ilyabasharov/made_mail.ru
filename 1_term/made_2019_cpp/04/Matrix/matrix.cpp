//
//  Matrix class realisation
//
//  matrix.cpp
//  Matrix
//
//  Created by Илья Башаров on 05/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "matrix.hpp"

pMatrix::pMatrix(std::vector<int> &row):
row(row)
{}

pMatrix::~pMatrix()
{}
 
int& pMatrix::operator [](const int j)
{
    if (j < 0 || j >= row.size())
        throw std::out_of_range{"Matrix::operator[][]"};
    else
        return row[j];
}
void pMatrix::operator = (const std::vector<int> &new_row)
{
    if (new_row.size() == row.size())
        row = new_row;
    else
        throw std::length_error{"pMatrix::operator = "};
}


Matrix::Matrix(const std::vector<std::vector<int>> &vec):
matrix(vec)
{}

Matrix::Matrix(const std::size_t rows, const std::size_t colomns, const int value):
matrix(std::vector<std::vector <int>>(rows, std::vector<int>(colomns, value)))
{}

Matrix::~Matrix()
{}

std::size_t Matrix::getRows() const
{
    return matrix.size();
}

std::size_t Matrix::getColumns() const
{
    if (matrix.size() == 0)
        throw std::out_of_range{"Matrix::GetColomns"};
    else
        return matrix[0].size();
}

pMatrix Matrix::operator [] (const int i)
{
    if (i < 0 || i >= matrix.size())
        throw std::out_of_range{"Matrix::operator[]"};
    else
        return pMatrix(matrix[i]);
}

Matrix Matrix::operator * (const int value) const
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return *this;
    
    Matrix a(matrix.size(), matrix[0].size());
    
    for (std::size_t i = 0; i < matrix.size(); i++)
        for (std::size_t j = 0; j < matrix[0].size(); j++)
            a.matrix[i][j] = matrix[i][j]*value;
    
    return a;
}

Matrix Matrix::operator * (const Matrix& other) const
{
    std::size_t r_this = getRows(), c_this = getColumns(),
    r_other = other.getRows(), c_other = other.getColumns();
    
    if (c_this == 0 || c_other == 0)
        throw std::out_of_range{"Matrix::operator * "};
    
    if (c_this != r_other)
        throw std::length_error{"Matrix::operator * "};
    
    Matrix c(r_this, c_other);
    
    for (std::size_t i = 0; i < r_this; i++)
        for (std::size_t j = 0; j < c_other; j++)
            for (std::size_t k = 0; k < c_this; k++)
                c.matrix[i][j] += matrix[i][k]*other.matrix[k][j];
    
    return c;
}

Matrix& Matrix::operator *= (const int value)
{
    std::size_t r_this = getRows(), c_this = getColumns();
    
    if (c_this == 0)
        return *this;
    
    for (std::size_t i = 0; i < r_this; i++)
        for (std::size_t j = 0; j < c_this; j++)
            matrix[i][j] *= value;
    return *this;
}

Matrix& Matrix::operator *= (const Matrix& other)
{
    *this = *this * other;
    return *this;
}

bool operator == (const Matrix& left, const Matrix& right)
{
    return left.matrix == right.matrix;
}

bool operator == (const Matrix& left, const std::vector<std::vector<int>> &vec)
{
    return left.matrix == vec;
}

bool operator != (const Matrix& left, const Matrix& right)
{
    return left.matrix != right.matrix;
}

std::ostream& operator << (std::ostream& out, const Matrix& matrix_)
{
    std::size_t rows = matrix_.getRows();
    std::size_t cols = matrix_.getColumns();
    
    if (cols == 0)
         throw std::out_of_range{"Matrix::operator << "};
    
    for (std::size_t i = 0; i < rows; i ++)
    {
        for (std::size_t j = 0; j < cols; j++)
            out << matrix_.matrix[i][j] << ' ';
        out << std::endl;
    }
    
    return out;
}
