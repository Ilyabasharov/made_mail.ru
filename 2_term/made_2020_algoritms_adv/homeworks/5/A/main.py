class PostfixSums:
    def __init__(self, array: list):
        self.sums = array
        
        for i in range(1, len(self.sums)):
            self.sums[i] = self.sums[i - 1] + self.sums[i]
    
    def request(self, left: int, right: int):
        return self.sums[right] - self.sums[left - 1] if left != 0 else self.sums[right]

if __name__ == '__main__':
    
    n, x, y, a_0 = [int(i) for i in input().split()]
    a = [a_0]*n
    
    pow_ = 1 << 16
    
    for i in range(1, n):
        a[i] = (x*a[i - 1] + y) % pow_
        
    sums = PostfixSums(a)
    
    m, z, t, b_0 = [int(i) for i in input().split()]
    b = [b_0]*(2*m)
    
    pow_ = 1 << 30
    
    for i in range(1, 2*m):
        b[i] = (z*b[i - 1] + t) % pow_
        
    for i in range(2*m):
        b[i] %= n
    
    output = 0
    for i in range(m):
        output += sums.request(min(b[2*i], b[2*i + 1]), max(b[2*i], b[2*i + 1]))
        
    print(output)
