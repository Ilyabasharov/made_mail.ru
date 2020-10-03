def merge(a: list, tmp: list, left: int, right: int, mid: int) -> int:
    
    i, j, count = 0, 0, 0
    
    while i + j < right - left:
        
        flag = (j < right - mid) and (a[i + left] > a[j + mid])
        
        if i == mid - left or flag:
            
            if j < right - mid:
                count += mid - (left + i)
                
            tmp[i + j] = a[j + mid]
            j += 1
        else:
            
            tmp[i + j] = a[i + left]
            i += 1
    
    for i in range(left, right):
        a[i] = tmp[i - left]
        
    return count
 
def merge_sort(a: list, tmp: list, left: int, right: int) -> int:
    
    count = 0
    
    if right - left <= 1:
        return count
    
    mid = (right + left) // 2
    
    count += merge_sort(a, tmp, left, mid)
    count += merge_sort(a, tmp, mid, right)
    count += merge(a, tmp, left, right, mid)
    
    return count
 
def count_inversion(a: list) -> int:
    
    tmp = [0]*len(a)
    
    return merge_sort(a, tmp, 0, len(a))
    
def main():
    
    n = int(input())
    array = [int(number) for number in input().split()]
    
    print(count_inversion(array))
 
if __name__ == '__main__':
    
    main()
