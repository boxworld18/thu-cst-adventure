import sys
import hashlib
import random
import string

N = 2000000
if __name__ == "__main__":
    f = open('testcases/test.txt', 'w')
    str = ''.join(random.choices(string.ascii_letters + string.digits, k = N))
    
    key = "0123456789abcdef"
    iv = "0123456789abcdef"
    
    f.write(str + '\n')
    f.write(key + '\n')
    f.write(iv + '\n')
    
    f.close()
    
    f = open('testcases/result.txt', 'w')
    data = bytes(str, 'utf-8')
    iv = bytes(iv, 'utf-8')
    key = bytes(key, 'utf-8')

    # encode the string
    encoded_str = str.encode()
    
    # create sha3-256 hash objects
    obj_sha3_256 = hashlib.sha3_256(encoded_str)
    
    # print in hexadecimal
    f.write("SHA3-256 Hash: " + obj_sha3_256.hexdigest())
    f.close()