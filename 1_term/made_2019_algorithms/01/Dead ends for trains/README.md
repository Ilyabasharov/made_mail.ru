# Hometask: Dead ends for trains

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to compile:
        -> make all
        
    if you want to clear all created files:
        -> make clear
        
#### There are a number of dead ends at the station where trains arrive.  A arriving and departuring time table is given for each train. The trains in the schedule are sorted by arrival time. When the train arrives, it is put into a dead end with a minimum name. At the same time, if the train goes from some deadlock departed at time X, then the train that arrives at time X cannot be put into this dead end, but  the train can put into this dead  at time X + 1. Write a program for calculating the minimum number of dead ends required for the station according to this schedule. 
Description:

#### Input format:

    ->  The first line contains the number of times for trains n. n ≤ 1 000 000 000.
        Each command is given as 2 integers: a b.
        a = arrival time
        a = departure time
       
#### Output format:

    ->  Minimum of necessary dead ends
    
        Examples:
        
        input       |   output
        1           |   1
        10 20       |
        ------------------------
        2           |   2
        10 20       |
        20 25       |
        ------------------------
        3           |   2
        10 20       |
        20 25       |
        21 30       |
        ------------------------
