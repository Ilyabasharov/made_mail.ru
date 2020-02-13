# Hometask: Queue with dynamic buffer

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to compile:
        -> make all
        
    if you want to clear all created files:
        -> make clear
        
#### The simple  Queue cah handle push back and pop front commands. Description:

#### Input format:

    ->  The first line contains the number of commands n. n ≤ 1,000,000.
        Each command is given as 2 integers: a b.
        a = 2 - pop front
        a = 3 - push back
        If pop front is given, then b is the expected value. If the pop front command is called for an empty data structure, then “-1” is expected.
       
#### Output format:

    ->  You should to print YES, if all expected values match. Otherwise, if at least one expectation did not materialize, print NO.
    
        Examples:
        
        input       |   output
        3           |   YES
        3 44        |
        3 50        |
        2 44        |
        ------------------------
        2           |   YES
        2 -1        |
        3 10        |
        2 10        |
        ------------------------
        2           |   NO
        3 44        |
        2 66        |
        ------------------------
