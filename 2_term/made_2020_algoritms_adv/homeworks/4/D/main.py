from random import randint

def miller_rabin_test(n):

    if (n < 6):
        if n == 1 or n == 4:
            return False
        else:
            return True

    f, s = 0, n - 1
    
    while s % 2 == 0:
        f += 1
        s //= 2
        
    for i in range(6):
    
        a = randint(2, n - 1)
        x = pow(a, s, n)
        
        if x == 1 or x == n - 1:
            continue
            
        for j in range(f - 1):
        
            x = pow(x, 2, n)
            
            if x == n - 1:
                break
        else:
            return False
            
    return True

if __name__ == '__main__':
    
    n = int(input())

    for i in range(n):
        print('YES') if miller_rabin_test(int(input())) else print('NO')

