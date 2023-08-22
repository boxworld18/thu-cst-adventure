import random
import string

N = 1000000
if __name__ == "__main__":
    f = open('testcases/test.txt', 'w')
    str = ''.join(random.choices(string.ascii_letters + string.digits, k = N))
    f.write(str + '\n')
    f.close()
    
    f = open('testcases/result.txt', 'w')
    f.write('Plaintext:  ' + str + '\n')
    f.close()