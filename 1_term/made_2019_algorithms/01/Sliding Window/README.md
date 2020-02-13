# Hometask: Queue for keeping maximum in each moment 

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to compile:
        -> make all
        
    if you want to clear all created files:
        -> make clear
        
#### Queue data structure which consists of 2 data structures like stack, supports basic operations like pop and push, getMax and isEmpty. The amortized cost of operations is  o(1). This queue was built for next task. Description:

#### Input format:

    ->  You have buffer with dimension n, n ≤ 100 000. Buffer numbers are located in range [-1e9, 1e9].  
    The first and second typed lines are responsible for dimension and buffer numbers.  
    Then you have iterators in that buffer which show you start and finish of window in buffer.  
    Also you can move the window usung increasing iterators with commands  'L' or 'R',   
    which means that the left iterator or right goes up his value.  
    The third and fourth lines point to amount of feature commands sequence 'L' or 'R', respectively. 
    See examples in the end of README file.
       
#### Output format:

    ->  You should type existed max in window for each moment after commands 'L' or 'R'.
    
        Examples:
        
        input                    |   output
        10                       |   4 4 4 4 5 8 8 8 8 8 8 6 
        1 4 2 3 5 8 6 7 9 10     |
        12                       |
        R R L R R R L L L R L L  |
        ----------------------------------------------------
