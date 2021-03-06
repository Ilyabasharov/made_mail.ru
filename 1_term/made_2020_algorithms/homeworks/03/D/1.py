from sys import stdin, stdout
 
def f(ropes: list, length: int) -> int:
    
    return sum(rope // length for rope in ropes)
 
def lower_bound_reversed(f, ropes: list,
                         left: int, right: int,
                         element: int) -> int:
    
    while left < right - 1:
        
        middle = left + (right - left) // 2
        
        if element >= f(ropes, middle):
            right = middle
        else:
            left = middle
    
    return left
    
def find_root(ropes: list, houses: int) -> float:
    
    l, r = 0, max(ropes) + 1
    
    return lower_bound_reversed(f, ropes, l, r, houses - 1)
    
def main():
    
    n, k = map(int, stdin.readline().split())
    
    ropes = [int(stdin.readline().rstrip()) for _ in range(n)]
    
    stdout.write(f'{find_root(ropes, k)}')
        
if __name__ == '__main__':
    main()
