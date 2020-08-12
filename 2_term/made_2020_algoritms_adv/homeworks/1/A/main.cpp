//
//  main.cpp
//  A task
//
//  Created by Илья Башаров on 27.02.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

std::vector<long int>::iterator getElement(std::vector<long int> &array, long int from, long int to)
{
    std::vector<long int>::iterator min_negative = array.begin() + from;
    
    for (auto iterator = array.begin() + from; iterator != array.begin() + to; iterator++)
    {
        if (*iterator >= 0)
            return iterator;
        else if (*iterator > *min_negative)
            min_negative = iterator;
    }
    
    return min_negative;
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    
    if (!input.is_open() || !output.is_open())
        return 0;
    
    long int N = 0, K = 0, position = 1, collected_money = 0;
    input >> N >> K;
    
    std::vector<long int> money_array(N, 0), step_array;
    
    for (long int i = 1; i < N - 1; ++i)
        input >> money_array[i];
    
    while (N - position > 0)
    {
        step_array.push_back(position);
        
        auto result = getElement(money_array,
                                 position,
                                 position + std::min(K, N - position));
        
        position = std::distance(money_array.begin(), result) + 1;
        collected_money += *result;
    }
    
    output << collected_money << std::endl << step_array.size() << std::endl;
    
    for (auto element : step_array)
        output << element << ' ';
    
    output << N << std::endl;
    
    input.close();
    output.close();
    
    return 0;
}
