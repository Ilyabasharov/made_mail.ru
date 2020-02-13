//
//  The program determines the largest number of occurrences in all possible subsegments.
//  All description you can see in repository.
//
//  main.cpp
//  Dead ends for trains
//
//  Created by Илья Башаров on 18/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#include "heap.hpp"

int how_many_trains_in_time(MinHeap &departures, int arrival_time, int departure_time, int count)
{
    if (departures.isEmpty())
    {
        departures.Insert(departure_time);
        return 1;
    }
    
    if (departures.GetMin() < arrival_time)
    {
        departures.ExtractMin();
        count --;
    }
    
    departures.Insert(departure_time);
    return ++count;
}

int main()
{
    MinHeap timetable;
    int trains_numbers = 0,
    arrival_time = 0, departure_time = 0,
    max_count = 0, count = 0;
    std::cin >> trains_numbers;
    
    for(int i = 0; i < trains_numbers; i++)
    {
        std::cin >> arrival_time >> departure_time;
        count = how_many_trains_in_time(timetable, arrival_time, departure_time, count);
        if (count > max_count)
            max_count = count;
    }
    std::cout << max_count << std::endl;
    
    return 0;
}
