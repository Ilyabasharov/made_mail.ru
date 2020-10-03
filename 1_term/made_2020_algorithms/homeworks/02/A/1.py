from sys import stdin, stdout
from random import randint
 
def split(l: int, r: int, x: int, array: int) -> int:
    
    m = l
    
    for i in range(l, r):
        
        if array[i] < x:
            array[i], array[m] = array[m], array[i]
            m += 1
            
    return m
 
def kStatistic(k: int, array: list) -> int:
    
    l, r = 0, len(array)
    
    while True:
        
        if r - l <= 1:
            return array[k]
        
        x = array[randint(l, r - 1)]
        m = split(l, r, x, array)
        
        if k < m:
            r = m
        else:
            l = m
    
def main():
    
    n = int(stdin.readline())
    array = list(map(int, stdin.readline().split()))
    m = int(stdin.readline())
    
    for _ in range(m):
        
        i, j, k = map(int, stdin.readline().split())
        
        tmp = array[i - 1:j]
        
        stdout.write('{}\n'.format(kStatistic(k - 1, tmp)))
    
if __name__ == '__main__':
    
    main()
