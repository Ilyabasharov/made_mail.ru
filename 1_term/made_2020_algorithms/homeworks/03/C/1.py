from sys import stdin, stdout
from math import log2, sqrt
 
def f(x: float, c: float) -> float:
    
    return x**2 + sqrt(x) - c
    
def find_root(c: float, eps: float = 1e-6) -> float:
    
    l, r = 0, c
    
    steps = int(log2((r - l) / eps))
    
    for _ in range(steps):
        
        m = l + (r - l) / 2
        
        if f(m, c) < 0:
            l = m
        else:
            r = m
    
    return (r + l) / 2
    
def main():
    
    c = float(stdin.readline())
    
    stdout.write('{0:.6f}'.format(find_root(c)))
        
if __name__ == '__main__':
    main()
