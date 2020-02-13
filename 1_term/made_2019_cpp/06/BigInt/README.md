# Hometask: Big int

## You should type on command line:
    
    if you want to pass tests:
        -> make test
    
    if you want to check:
        -> make run
        
    if you want to clear all created files:
        -> make clean
        

#### You should create class for big numbers. The size of the number is limited only by the size of the memory. 
It is necessary to support the semantics of working with a regular int.

```c++
BigInt a = 1;
BigInt b = a;
BigInt c = a + b + 2;
```
Implement the operator of output to the stream, addition, subtraction, unary minus, all comparison operations.

std :: vector and other containers cannot be used - manage the memory by yourself.
