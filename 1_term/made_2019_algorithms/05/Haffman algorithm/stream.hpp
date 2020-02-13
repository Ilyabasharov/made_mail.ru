//
//  stream.hpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 09/12/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef stream_hpp
#define stream_hpp

#include <iostream>
#include <vector>
#include <fstream>

typedef unsigned char byte;

struct IInputStream
{
    virtual bool Read(byte&) = 0;
};

struct IOutputStream
{
    virtual void Write(byte) = 0;
};

class CInputStream : public IInputStream
{
public:
    CInputStream(const std::vector<byte>&);
    virtual bool Read(byte&);

private:
    unsigned int index;
    const std::vector<byte>& body;
};

class COutputStream : public IOutputStream
{
public:
    COutputStream(std::vector<byte>&);
    virtual void Write(byte);

private:
    std::vector<byte>& body;
};

void fillInputs(std::vector<std::vector<byte>>&);
bool isEqual(const std::vector<byte>&, const std::vector<byte>&);
int calculateSize(const std::vector<std::vector<byte>>&);

#endif /* stream_hpp */
