//
//  tests.cpp
//  Sorting long sequence
//
//  Created by Илья Башаров on 31/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#include "sorted_window.hpp"
#include "tests.hpp"

void test(std::function<void (std::vector<long int> &array, unsigned int n)> a,
          unsigned int n, unsigned int k)
{
    std::vector<long int> buffer;
    a(buffer, n);
    std::vector<long int> current(k, 0);
    unsigned long int dim = n / k;
    for (unsigned long int j = 0; j < k; j++)
        current[j] = buffer[j];
    
    SortedWindow window(current);
    
    for (unsigned long int i = 0; i < dim - 1; i++)
    {
        for (unsigned long int j = 0; j < k; j++)
            current[j] = buffer[(i+1)*k + j];
        window.AnalyseFirstKMinElements(current);
    }
    
    current.clear();
    
    if (n % k != 0)
    {
        for (unsigned long int j = 0; j < n % k; j++)
            current.push_back(buffer[dim*k + j]);
        
        window.AnalyseFirstKMinElements(current);
    }
    
    std::sort(buffer.begin(), buffer.end());
    
    for (unsigned int i = 0; i < k; i++)
        if(window.GetElement(i) != buffer[i])
        {
            std::cout << "What happend with: " << window.GetElement(i) <<
            ", and with: " << buffer[i] << "? Index is: " << i << '.' << std::endl;
            assert(false);
        }
    std::cout << '.';
}

void tests()
{
    /*--------------------------------FIRST-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back((rand() % 100000)*(-1));
    }, 1000,  40);
    
    /*--------------------------------SECOND-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back((rand() % 10000000)*((rand() % 2)*2 - 1));
    }, 1000000, 30);
    
    /*--------------------------------THIRD-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back((rand() % 100000000));
    }, 1000000,  1000);
    
    /*--------------------------------FOURTH-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back(2);
    }, 11000,  5);
    
    /*--------------------------------FIFTH-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back(i + rand()%4);
    }, 110000,  11500);
    
    /*--------------------------------SIXTH-TEST----------------------------------*/
    test([](std::vector<long int> &array, unsigned int n) -> void {
        for (unsigned int i = 0; i < n; i++)
            array.push_back(i);
    }, 110000,  12500);
    
    std::cout << std::endl << "Testing was ended successfully." << std::endl;
}

int main()
{
    tests();
    return 0;
}
