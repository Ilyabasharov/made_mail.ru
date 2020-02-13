//
//  Find Maximum in a sliding window
//
//  main.cpp
//  Sliding Window
//
//  Created by Илья Башаров on 22/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "queue.hpp"

int main()
{
    MaxQueue queue;
    std::vector<long int> buffer;
    unsigned int number_of_commands = 0;
    long int value = 0;
    std::cin >> number_of_commands;
    
    for (unsigned int i = 0; i < number_of_commands; i++)
    {
        std::cin >> value;
        buffer.push_back(value);
    }
    
    char command = 0;
    std::cin >> number_of_commands;
    unsigned int right = 0;
    queue.push(buffer[right++]);
    for (unsigned int i = 0; i < number_of_commands; i++)
    {
        std::cin >> command;
        switch (command)
        {
            case 'R':
                queue.push(buffer[right++]);
                std::cout << queue.getMax() << ' ';
                break;
                
            case 'L':
                queue.pop();
                std::cout << queue.getMax() << ' ';
                break;
                
            default:
                break;
        }
    }
    std::cout << std::endl;
    return 0;
}
