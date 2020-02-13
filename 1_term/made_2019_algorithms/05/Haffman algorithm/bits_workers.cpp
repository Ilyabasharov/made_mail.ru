//
//  bits_writer.cpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 10/12/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "bits_workers.hpp"

void BitsWriter::WriteBit(bool bit)
{
    accumulator |= bit << bits_count++;
    if (bits_count == 8)
    {
        bits_count = 0;
        buffer.push_back(accumulator);
        accumulator = 0;
    }
}

void BitsWriter::WriteByte(byte byte_)
{
    if (bits_count == 0)
        buffer.push_back(byte_);
    else
    {
        accumulator |= byte_ << bits_count;
        buffer.push_back(accumulator);
        accumulator = byte_ >> (8 - bits_count);
    }
}

std::vector<byte> BitsWriter::GetResult()
{
    if (bits_count != 0)
        buffer.push_back(accumulator);
    
    buffer.push_back(static_cast<byte>(bits_count));
    return std::move(buffer);
}

bool BitsReader::ReadBit(IInputStream &stream, bool& input)
{
    if (bits_count == 8)
    {
        bits_count = 0;
        if (!stream.Read(value))
            return false;
    }
    input = (value >> bits_count++) & true;
    return true;
}

bool BitsReader::ReadByte(IInputStream& stream, byte& input)
{
    if (bits_count == 8)
        return stream.Read(input);
    
    byte temp = 0;
    if (!stream.Read(temp))
        return false;
    
    value = value >> bits_count;
    value |= temp << (8 - bits_count);
    input = value;
    value = temp;
    
    return true;
}
