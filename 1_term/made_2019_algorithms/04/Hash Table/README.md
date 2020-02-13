# Hometask: Dynamic hash table with double hashing

## You should type on command line:
    
    if you want to run:
        -> make run
        
    if you want to clear all created files:
        -> make clean
        
#### Implementation of a multi-row data structure based on a dynamic hash table. Stored strings are non-empty and consist of lowercase latin letters. The hash function of the string must be implemented by calculating the values ​​of the polynomial by the Horner method. The initial size of the table must be equal to 8. Rehashing performed when adding elements in the case when the fill factor of the table corresponds to 3/4.

#### Input format:

    -> Each line of input defines one operation on the set. An operation record consists of the type of operation and the space following which the operation is performed, followed by a space. 
    -> The type of operation is one of three characters: + means adding this line to the set; - means removing a string from the set; ? means checking whether a given string belongs to a set. 
    -> When you add an item to a set, it is NOT WARRANTED that it is not in the set. When you remove an element from a set, it is NOT WARRANTED that it is present in this set.
       
#### Output format:

    ->  The program should print for each operation one of the two lines OK or FAIL.
    -> For the operation '?': OK, if the element is present in the set else FAIL.
    -> For the operation '+': FAIL, if the added element is already present in the set and therefore cannot be added, else OK.
    For the operation '-': OK, if the element was present in the set and was successfully deleted, else FAIL.
    
        Example:
        
        input              |   output
        + hello            |    OK
        + bue              |    OK
        ? bue              |    OK
        + bue              |    FAIL
        - bue              |    OK
        ? bue              |    FAIL
        ? hello            |    OK
        ---------------------------------------------------
        
        
