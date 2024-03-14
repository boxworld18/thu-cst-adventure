import random
import string

N = 100
M = 10 + 1
TAR = [i for i in range(1, M)]

if __name__ == "__main__":
    f = open('testcases/test.txt', 'w')
    res = random.choices(TAR, k = N)
    str = '\n'.join([str(ctx) for ctx in res])
    f.write(str + '\nend\n')
    f.close()
    
    tar = '====== RESULT ======\n'
    for i in range(1, M):
        cnt = res.count(i)
        tar += 'Cand# {:3}: {:8}\n'.format(i, cnt)
    tar += '====================\n'
        
        
    f = open('testcases/result.txt', 'w')
    f.write(tar)
    f.close()