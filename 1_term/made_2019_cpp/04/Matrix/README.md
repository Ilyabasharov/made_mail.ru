# Hometask: Matrix realisation with using proxy class

## You should type on command line:
    
    if you want to pass tests:
        -> make test
        
    if you want to clear all created files:
        -> make clean
        

#### Required to write matrix class with type of elements - int.
You need to set amount of rows and columns in constructor. Operations dicribed below must be implemented:
    -> get rows/colomns
    -> get element from given index
    -> multiply by number
    -> compare using != and ==

In case of an error of going abroad, throw an exception:
```c++
throw std::out_of_range("")
```

#### Example:
```c++
const size_t rows = 5;
const size_t cols = 3;

Matrix m(rows, cols);

assert(m.getRows() == 5);
assert(m.getColumns() == 3);

m[1][2] = 5; // строка 1, колонка 2
double x = m[4][1];

m *= 3; // умножение на число

Matrix m1(rows, cols);

if (m1 == m)
{
}
```
