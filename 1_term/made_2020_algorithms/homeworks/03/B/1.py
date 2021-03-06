from sys import stdin, stdout
 
class FastCounter:
    
    def __init__(self,
                 array: list):
        array.sort()
        self.array = array
        
    def count(self,
              left_element: int,
              right_element: int):
        
        left_index = self.lower_bound(left_element)
        
        if left_index == len(self.array):
            return 0
        else:
            right_index = self.lower_bound(right_element + 1, left = left_index - 1)
            
            return right_index - left_index
    
    def lower_bound(self,
                    element: int,
                    left: int = None,
                    right: int = None):
        
        if not left:
            left = -1
        if not right:
            right = len(self.array)
            
        while left < right - 1:
        
            middle = left + (right - left) // 2
        
            if element <= self.array[middle]:
                right = middle
            else:
                left = middle
    
        return right
    
def main():
    
    n = int(stdin.readline())
    array = list(map(int, stdin.readline().split()))
    
    counter = FastCounter(array)
    
    k = int(stdin.readline())
    
    for _ in range(k):
        
        l, r = map(int, stdin.readline().split())
        stdout.write(f'{counter.count(l, r)} ')
    
if __name__ == '__main__':
    main()
