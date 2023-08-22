def exgcd(a, b):
    if b == 0:
        return 1, 0, a
    else:
        x, y, q = exgcd(b, a % b)
        x, y = y, (x - (a // b) * y)
        return x, y, q

def ModReverse(a, p):
    x, _, q = exgcd(a, p)
    if q != 1:
        raise Exception("No solution.")
    else:
        return (x + p) % p 
    
def find(a, p, c):
    """
    a * b = c mod p
    """
    while a < 0:
        a += p
    while c < 0:
        c += p
    b = 0
    s = 0
    while True:
        if s % p == c:
            return b
        else:
            b += 1
            s = (s + a) % p
    
def find_exp(a, p, c):
    """
    a ^ b = c mod p
    """
    while a < 0:
        a += p
    while c < 0:
        c += p
    b = 0
    s = 1
    while True:
        if s % p == c:
            print(b)
            # return b
            b += 1
            s = (s * a) % p
        else:
            b += 1
            s = (s * a) % p
        if b > 1000000:
            break

p = 31847
gamma = 23972
alpha = 5
beta = 25703

a = find_exp(alpha, p, beta)
k = find_exp(alpha, p, gamma)
delta = 31396
k_inv = find(10915, p - 1, -22425)

a1 = find(23972, p - 1, 8990 - 31396 * k)
print(a, k, k_inv, a1)