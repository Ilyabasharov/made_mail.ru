def sort(array: list) -> None:
    
    for i in range(len(array)):
        
        j = i
        
        while j > 0 and array[j - 1] > array[j]:
            
            array[j], array[j - 1] = array[j - 1], array[j]
            j -= 1
            
def main():

    n = int(input())
    array = [int(number) for number in input().split()]
    
    sort(array)
    
    print(*array)
    
if __name__ == '__main__':
    
    main()
