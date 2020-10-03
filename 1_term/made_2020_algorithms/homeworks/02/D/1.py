from sys import stdin, stdout
 
def counter(string: str, left: int, right: int) -> dict:
    
    ''' Counting list for string[left, right]
    string: str - what we want to code as counting list
    left:   int - left bound
    right:  int - right bound
    
    return counting coded list
    
    '''
    
    result = [0]*26
    
    for index in range(left, right):
        new_index = ord(string[index]) - ord('a')
        result[new_index] += 1
            
    return result
 
def canCreateFromOther(dict_s: list, dict_t: dict) -> bool:
    
    ''' Can we reproduce dict_s from symbols in dict2 ?
    dict_s:  list - string which is coded using counting list
    dict_t:  int  - symbols which is coded using counting list
    
    return True if we can else False
    '''
    
    for amount_s, amount_t in zip(dict_s, dict_t):
        if amount_s > amount_t:
            return False
    
    return True
 
def howMany(s: str, t: str) -> int:
    
    ''' How many substrings from t can we reproduce for s?
    s: str - base str
    t: available symbols
    
    return number of ways
    '''
                                
    left, right, result = 0, 0, 0
    
    dict_t = counter(t, 0, len(t))
    dict_s = counter(s, 0, 1)
    
    while right < len(s):
        
        diff = right - left + 1
        
        if canCreateFromOther(dict_s, dict_t):
            
            result += diff
            
            right += 1
            
            if right < len(s):
                dict_s[ord(s[right]) - ord('a')] += 1
            
        else:
            dict_s[ord(s[left]) - ord('a')] -= 1
            
            left += 1
            
            if diff == 1:
                
                right += 1
                
                if right < len(s):
                    dict_s[ord(s[right]) - ord('a')] += 1
        
    return result
 
def main():
    
    n, m = map(int, stdin.readline().split())
    
    s = stdin.readline().rstrip()
    t = stdin.readline().rstrip()
    
    stdout.write(f'{howMany(s, t)}')
    
if __name__ == '__main__':
    main()
