//
//  bits_writer.hpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 10/12/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef bits_writer_hpp
#define bits_writer_hpp

#include "stream.hpp"

class BitsWriter
{
public:
    void WriteBit(bool bit);
    void WriteByte(byte byte);
    std::vector<byte> GetResult();

private:
    std::vector<byte> buffer;
    byte accumulator = 0;
    byte bits_count = 0;
};

class BitsReader
{
public:
    bool ReadBit(IInputStream&, bool&);
    bool ReadByte(IInputStream&, byte&);
private:
    byte value = 0;
    byte bits_count = 8;
};

#endif /* bits_writer_hpp */
