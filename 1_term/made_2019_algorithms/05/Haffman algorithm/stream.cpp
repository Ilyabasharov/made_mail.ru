//
//  stream.cpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 09/12/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "stream.hpp"

CInputStream::CInputStream(const std::vector<byte>& body):
index(0), body(body)
{}

bool CInputStream::Read(byte& value)
{
    if (index >= body.size())
        return false;

    value = body[index++];
    
    return true;
}

COutputStream::COutputStream(std::vector<byte>& body):
body(body)
{
    body.clear();
}

void COutputStream::Write(byte value)
{
    body.push_back(value);
}

void fillInputs(std::vector<std::vector<byte>>& inputs)
{
    inputs.clear();

    std::string currentFileName;
    while (getline(std::cin, currentFileName))
    {
        if (currentFileName.empty())
            continue;

        inputs.push_back(std::vector<byte>());

        std::ifstream file;
        file.open(currentFileName.c_str());

        byte value;
        while (file >> value)
            (*inputs.rbegin()).push_back(value);
    }
}

bool isEqual(const std::vector<byte>& v1, const std::vector<byte>& v2)
{
    if (v1.size() != v2.size())
        return false;

    for (unsigned int i = 0; i < v1.size(); i++)
        if(v1[i] != v2[i])
            return false;
    
    return true;
}

int calculateSize(const std::vector<std::vector<byte>>& array)
{
    int result = 0;
    for (unsigned int i = 0; i < array.size(); i++)
    {
        const std::vector<byte>& data = array[i];
        result += data.size();
    }

    return result;
}
