def lower_bound(array: list, element: int):
    
    left, right = -1, len(array)
    
    while left < right - 1 :
        
        middle = (left + right) // 2
        
        if element <= array[middle]:
            right = middle
        else:
            left = middle
    
    return left, right
        
def main():
    n, k = map(int, input().split())
    
    array = list(map(int, input().split()))
    requests = list(map(int, input().split()))
    
    for i in range(k):
        
        left, right = lower_bound(array, requests[i])
        
        if left < 0:
            print(array[right])
        elif right == len(array):
            print(array[left])
        else:
            if abs(array[left]  - requests[i]) > \
               abs(array[right] - requests[i]):
                print(array[right])
            else:
                print(array[left])
 
if __name__ == '__main__':
    main()
