from sys import stdin, stdout

def countingSort(array: list, n: int) -> None:
    
    database = [0]*(n + 1)
    
    for number in array:
        database[number] += 1
    
    j = 0
    
    for i in range(n + 1):
        for k in range(database[i]):
            array[j] = i
            j += 1
            
def main():
    
    array = list(map(int, stdin.readline().split()))
    countingSort(array, 100)
    
    stdout.write(' '.join(map(str, array)))
    
if __name__ == '__main__':
    
    main()
