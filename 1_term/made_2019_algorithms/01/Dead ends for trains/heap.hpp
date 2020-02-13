//
//  heap.hpp
//  Dead ends for trains
//
//  Created by Илья Башаров on 29/10/2019.
//  Copyright © 2019 Илья Башаров. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <iostream>
#include <vector>
#include <algorithm>


class MinHeap
{
private:
    std::vector<int> buffer;
    
public:
    MinHeap();
    ~MinHeap();
    int GetMin();
    void Insert(int value);
    int ExtractMin();
    bool isEmpty();
    void SiftUp(int index);
    void SiftDown(int index);
    void print();
};

#endif /* heap_hpp */
