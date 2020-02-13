//
//  The realisation of Queue with dynamic buffer
//
//  main.cpp
//  Queue with dynamic buffer
//
//  Created by Илья Башаров on 17/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "queue.hpp"

int main()
{
    QueueWithDynamicBuffer queue;
    
    unsigned long int commands_number = 0;
    std::cin >> commands_number;
    for (unsigned long int i = 0; i < commands_number; i++)
    {
        char command = 0;
        long int value = 0;
        std::cin >> command >> value;
        switch (command)
        {
            case '2':
                if (queue.pop_front() != value)
                {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
                
            case '3':
                queue.push_back(value);
                
            default:
                break;
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
