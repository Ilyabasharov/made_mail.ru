//
//  SortedWindow realisation.
//
//  sorted_window.hpp
//  Sorting long sequence
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef sorted_window_hpp
#define sorted_window_hpp

#include <iostream>
#include <vector>
#include <cstring>
#include <functional>

class SortedWindow
{
private:
    std::vector<long int> window;
    
public:
    SortedWindow(std::vector<long int> &buffer);
    ~SortedWindow();
    void AnalyseFirstKMinElements(std::vector<long int> &buffer);
    void PrintWindow();
    long int GetElement(int index);
};

bool cmp (long int a, long int b);
void my_qsort(std::vector<long int>::iterator first,
           std::vector<long int>::iterator last,
           std::function<bool(long int a, long int b)> compare);

#endif /* sorted_window_hpp */
