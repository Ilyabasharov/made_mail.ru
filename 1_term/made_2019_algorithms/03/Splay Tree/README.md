# Hometask: Splay tree for finding k-order statistic

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to clear all created files:
        -> make clean
        
#### Was given long long whole numbers sequence with length N. You should create splay tree for finding k-order statistic.

#### Input format:

    ->  The first line contains the number of elements in sequence N, N < 10^6.
    ->  The second line contains long long sequence with elements in range long long int and k order statistic.
       
#### Output format:

    ->  You should to print in each time k order statistic in sequence.
    
        Example:
        
        input                 |   output
        3                     |   1 1 2
        1 0                   |
        -1 0                  |
        2 0                   |
        ---------------------------------------------------
        5                     |   40 40 10 4 50
        40 0                  |
        10 1                  |
        4 1                   |
        -10 0                 |
        50 2                  |
        ---------------------------------------------------

#### How it works : Splay Tree Visualisation using Graphviz library

    -> how to install [https://www.graphviz.org]
    -> Program will create graph.gv. You should open it and enjoy. After each time when you
    will want to add/erase element, the file will record and graphviz will show you changes.
    
