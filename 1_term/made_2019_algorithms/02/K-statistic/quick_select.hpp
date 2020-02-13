//
//  quick_select.hpp
//  K-statistic
//
//  Created by Илья Башаров on 30/10/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef quick_select_hpp
#define quick_select_hpp

#include <iostream>
#include <vector>
#include <cstdlib>

unsigned long int Partition(std::vector<int> &buffer,
                            const unsigned long int left,
                            const unsigned long int right);

unsigned long int RandomPivotPartition(std::vector<int> &buffer,
                                       const unsigned long int left,
                                       const unsigned long int right);

int QuickSelect(std::vector<int> &buffer, const unsigned int k);

#endif /* quick_select_hpp */
