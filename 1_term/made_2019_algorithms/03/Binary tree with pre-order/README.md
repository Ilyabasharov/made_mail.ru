# Hometask: Non-recursive binary tree pre-order traversal

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to clear all created files:
        -> make clear
        
#### Was given long long whole numbers sequence with length N. You should create binary tree with naive insertion order, i. e. if you want to add key named K to tree and K < root key, you should to link this key to left subtree otherwise to right subtree. Task is print all tree elements in pre-order traversal.

#### Input format:

    ->  The first line contains the number of elements in sequence N, N < 10^6.
    ->  The second line contains long long sequence with elements in range long long int.
       
#### Output format:

    ->  You should to print print all tree elements in pre-order traversal.
    
        Example:
        
        input                     |   output
        10                        |   2 1 5 4 3 6 7 8 9 10
        2 5 6 4 7 8 9 3 1 10      |
        ---------------------------------------------------
        10                        |   5 4 3 2 1 9 7 6 8 10
        5 9 4 3 7 2 6 10 1 8      |
        ---------------------------------------------------
        10                        |   1 5 2 4 3 10 8 7 6 9
        1 5 10 2 4 3 8 9 7 6      |
        ---------------------------------------------------
        
