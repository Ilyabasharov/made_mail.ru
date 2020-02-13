//
//  main.cpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 28/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "haffman.hpp"

int main()
{
    std::vector<std::vector<byte>> input;

    fillInputs(input);
    
    std::vector<std::vector<byte>> compressed(input.size());
    
    try
    {
        for (std::size_t i = 0; i < input.size(); i++)
        {
            CInputStream iStream(input[i]);
            COutputStream oStream(compressed[i]);
            Encode(iStream, oStream);
        }
        
        for (std::size_t i = 0; i < input.size(); i++)
        {
            std::vector<byte> output;
            CInputStream iStream(compressed[i]);
            COutputStream oStream(output);
            Decode(iStream, oStream);
            if (!isEqual(input[i], output))
            {
                std::cout << "Input and output aren't equal" << std::endl;
                return 0;
            }
        }
    }
    
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid_argument: " << ia.what() << std::endl;
    }

    std::cout << "Compression persentage:" << (100. * calculateSize(compressed) / calculateSize(input)) << std::endl;

    return 0;
}
