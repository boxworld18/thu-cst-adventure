import Crypto.Cipher.AES as AES
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
    str += chr(16 - N % 16) * (16 - N % 16)
    data = bytes(str, 'utf-8')
    iv = bytes(iv, 'utf-8')
    key = bytes(key, 'utf-8')

    decipher = AES.new(key=key, mode=AES.MODE_CBC, iv=iv)
    enc = decipher.encrypt(data)
    f.write('Cipher: \n' + enc.hex('\n', 16) + '\n')
    
    decipher = AES.new(key=key, mode=AES.MODE_CBC, iv=iv)
    dec = decipher.decrypt(enc).decode('ascii')
    
    res = [dec[i: i + 16] for i in range(0, len(dec), 16)]
    res = '\n'.join(res).strip(chr(16 - ord(res[-1][-1]) % 16))
    f.write('Decrypted: \n' + res + '\n')
    f.close()