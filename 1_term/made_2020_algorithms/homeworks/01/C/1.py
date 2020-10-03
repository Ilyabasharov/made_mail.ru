from random import randint
 
def partition(l: int, r: int, x: int, array: list) -> int:
    
    i, j = l, r
    
    while i <= j:
        
        while array[i] < x:
            i += 1
        
        while array[j] > x:
            j -= 1
            
        if i < j:
            array[i], array[j] = array[j], array[i]
            i += 1
            j -= 1
        else:
            break
    
    return j
    
 
def sort(l: int, r: int, array: list) -> None:
    
    if l >= r:
        return
    
    x = array[randint(l, r - 1)]
    m = partition(l, r, x, array)
    
    sort(l, m, array)
    sort(m + 1, r, array)

def qsort(array: list) -> None:
    
    if len(array) < 2:
        return
    
    sort(0, len(array) - 1, array)
    
def main():
    
    n = int(input())
    array = [int(number) for number in input().split()]
    
    qsort(array)
    
    print(*array)
    
if __name__ == '__main__':
    
    main()
