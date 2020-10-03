from sys import stdin, stdout

def countingSort(data: list,
                 indexes: list,
                 step: int,
                 m: int) -> None:
    
    ''' data:    list - database with strings which have to be sorted
        indexes: list - additional array for avoiding copy strings
        step:    int  - radix sort step
        m:       int  - strings length
    '''
    
    dict_base = [[] for i in range(26)]
    
    for index in indexes:
        char = data[index][m - 1 - step]
        dict_base[ord(char) - ord('a')].append(index)
    
    j = 0
    
    for i in range(26):
        for new_index in dict_base[i]:
            indexes[j] = new_index
            j += 1
            
def radixSort(data: list,
              n: int,
              m: int,
              k: int) -> list:
    
    ''' data: list - database with strings which have to be sorted
        n:    int  - database length
        m:    int  - length of each element in database
        k:    int  - amount of steps in radixSort
    '''
    
    indexes = [i for i in range(n)]
    
    for i in range(k):
        countingSort(data, indexes, i, m)
        
    return indexes
        

def main():
    n, m, k = map(int, stdin.readline().split())
    
    database = [stdin.readline() for _ in range(n)]
        
    indexes = radixSort(database, n, m, k)
    
    stdout.write('\n'.join(database[i] for i in indexes))
        
if __name__ == '__main__':
    main()
