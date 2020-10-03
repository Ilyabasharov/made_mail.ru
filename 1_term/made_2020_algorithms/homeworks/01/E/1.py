def merge(a: list, tmp: list, left: int, right: int, mid: int) -> None:
    
    i, j = 0, 0
    
    while i + j < right - left:
        
        if i == mid - left or (j < right - mid) and (a[i + left] > a[j + mid]):
                
            tmp[i + j] = a[j + mid]
            j += 1
        else:
            
            tmp[i + j] = a[i + left]
            i += 1
    
    for i in range(left, right):
        a[i] = tmp[i - left]
 
def merge_sort(a: list, tmp: list, left: int, right: int) -> None:
    
    if right - left <= 1:
        return
    
    mid = (right + left) // 2
    
    merge_sort(a, tmp, left, mid)
    merge_sort(a, tmp, mid, right)
    merge(a, tmp, left, right, mid)
    
def main():
    
    n = int(input())
    array = [int(number) for number in input().split()]
    tmp = [0]*len(array)
    merge_sort(array, tmp, 0, len(array))
    
    print(*array)
 
if __name__ == '__main__':
    
    main()
