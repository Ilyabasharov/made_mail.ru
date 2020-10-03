from random import randint
 
class RomanToArabic:
    
    def __init__(self):
        self.roman = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
        
    def to_arabic(self, roman: str) -> int:
        
        arabic = 0
        
        for i in range(len(roman)):
            
            if i > 0 and self.roman[roman[i]] > self.roman[roman[i - 1]]:
                arabic += self.roman[roman[i]] - 2*self.roman[roman[i - 1]]
            else:
                arabic += self.roman[roman[i]]
                
        return arabic
 
def partition(l: int, r: int, x: int, array: list) -> int:
    
    i, j = l, r
    
    while i <= j:
        
        while array[i] < x:
            i += 1
        
        while array[j] > x:
            j -= 1
            
        if i < j:
            array[i], array[j] = array[j], array[i]
            i += 1
            j -= 1
        else:
            break
    
    return j
    
def sort(l: int, r: int, array: list) -> None:
    
    if l >= r:
        return
    
    x = array[randint(l, r - 1)]
    m = partition(l, r, x, array)
    
    sort(l, m, array)
    sort(m + 1, r, array)
    
def qsort(array: list) -> None:
    
    if len(array) < 2:
        return array
    
    return sort(0, len(array) - 1, array)
                    
def main():
    
    n = int(input())
    
    data_kings = dict()
    
    from_roman = RomanToArabic()
    from_arabic = dict()
    
    for i in range(n):
        
        king, roman = input().split()
        
        arabic = from_roman.to_arabic(roman)
        
        if king in data_kings:
            data_kings[king].append(arabic)
        else:
            data_kings[king] = [arabic]
        
        from_arabic[arabic] = roman
            
    sorted_keys = [*data_kings]
    qsort(sorted_keys)
    
    for key in sorted_keys:
        
        qsort(data_kings[key])
        
        for arabic_number in data_kings[key]:
            print('{} {}'.format(key, from_arabic[arabic_number]))
    
 
if __name__ == '__main__':
    
    main()
