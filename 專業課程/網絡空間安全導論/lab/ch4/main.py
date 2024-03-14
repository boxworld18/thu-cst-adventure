import os
import time
import socket
import hashlib
import random
import string
from Crypto import Random
from Crypto.Cipher import DES, AES
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5 as PKCS1_cipher
from base64 import b64encode, b64decode

HOST = 'localhost'
PORT = 3890
BUF = 10000

class AESCipher:
    def __init__(self, key):
        self.block_size = 16 # AES.block_size
        self.key = hashlib.sha256(key.encode()).digest()

    def __pad(self, plain_text):
        number_of_bytes_to_pad = self.block_size - len(plain_text) % self.block_size
        ascii_string = chr(number_of_bytes_to_pad)
        padding_str = number_of_bytes_to_pad * ascii_string
        padded_plain_text = plain_text + padding_str
        return padded_plain_text

    @staticmethod
    def __unpad(plain_text):
        last_character = plain_text[len(plain_text) - 1:]
        return plain_text[:-ord(last_character)]
    
    def encrypt(self, plain_text):
        plain_text = self.__pad(plain_text)
        iv = Random.new().read(self.block_size)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        encrypted_text = cipher.encrypt(plain_text.encode())
        return b64encode(iv + encrypted_text)

    def decrypt(self, encrypted_text):
        encrypted_text = b64decode(encrypted_text)
        iv = encrypted_text[:self.block_size]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        plain_text = cipher.decrypt(encrypted_text[self.block_size:]).decode("utf-8")
        return self.__unpad(plain_text)
    
class DESCipher:
    def __init__(self, key: str):
        self.key = key.encode()
        self.block_size = 8
    
    def __pad(self, plain_text):
        number_of_bytes_to_pad = self.block_size - len(plain_text) % self.block_size
        ascii_string = chr(number_of_bytes_to_pad)
        padding_str = number_of_bytes_to_pad * ascii_string
        padded_plain_text = plain_text + padding_str
        return padded_plain_text

    @staticmethod
    def __unpad(plain_text):
        last_character = plain_text[len(plain_text) - 1:]
        return plain_text[:-ord(last_character)]
    
    def encrypt(self, plain_text):
        plain_text = self.__pad(plain_text)
        iv = Random.new().read(self.block_size)
        cipher = DES.new(self.key, DES.MODE_CBC, iv)
        encrypted_text = cipher.encrypt(plain_text.encode('utf8'))
        return b64encode(iv + encrypted_text)
    
    def decrypt(self, encrypted_text):
        encrypted_text = b64decode(encrypted_text)
        iv = encrypted_text[:self.block_size]
        cipher = DES.new(self.key, DES.MODE_CBC, iv)
        plain_text = cipher.decrypt(encrypted_text[self.block_size:]).decode("utf-8")
        return self.__unpad(plain_text)
    
    def encrypt_zh(self, plain_text):
        txt = b64encode(plain_text.encode('utf-8')).decode('utf-8')
        return self.encrypt(txt)
    
    def decrypt_zh(self, encrypted_text):
        res = self.decrypt(encrypted_text)
        return b64decode(res.encode('utf-8')).decode('utf-8')

class Client:
    def __init__(self, sk):
        self.shared_key = sk
        self.aes = AESCipher(self.shared_key)
    
    def run(self):
        s = socket.socket()
        s.connect((HOST, PORT))
        
        print('------ ROUND 1 ------')
        # 1.1 gen RSA key pair
        random_generator = Random.new().read
        key = RSA.generate(1024, random_generator)
        msg1_inner = key.publickey().exportKey('PEM').decode('cp1252')
        
        # 1.2 send public key to server
        msg1 = self.aes.encrypt(msg1_inner)
        s.sendall(msg1)
        print('[A] send: \n', msg1)
        
        
        # 3.1 receive communication key from server
        msg2 = s.recv(BUF)
        msg2_inner = self.aes.decrypt(msg2)
        # print('[A] recv: \n', msg2_inner)
        
        rsa_dec = PKCS1_cipher.new(key)
        secc_enc = b64decode(msg2_inner.encode('ascii'))
        secc_key = rsa_dec.decrypt(secc_enc, 0).decode('utf8')
        print('[A] Session Key: \n', secc_key)
        des = DESCipher(secc_key)
        
        print('\n------ ROUND 3 ------')
        # 3.2 gen random number NA
        na = ''.join(random.choices(string.digits, k = 20))
        print('[A] N_a = ', na)
        
        msg3 = des.encrypt(na)
        print('[A] send: ', msg3)
        s.sendall(msg3)
        
        # 5.1 receive NA || NB
        msg4 = s.recv(BUF)
        nab = des.decrypt(msg4)
        print('[A] N_a || N_b = ', nab)
        
        # 5.2 check NA
        na_recv = nab[:20]
        assert na == na_recv, 'na != na_recv'
        print('[A] Check N_a: OK')
        
        print('\n------ ROUND 5 ------')
        # 5.3 send NB for checking
        nb = nab[20:]
        print('[A] N_b = ', nb)
            
        msg5 = des.encrypt(nb)
        print('[A] send: ', msg5)
        s.sendall(msg5)
        
        time.sleep(2)
        while True:
            msg = input('[A] Your msg: ')
            en_msg = des.encrypt_zh(msg)
            print('[A] send: ', en_msg)
            s.sendall(en_msg)
            
            data = s.recv(BUF)
            if not data:
                break
            print('[A] recv: ', des.decrypt_zh(data))
            print()


class Server:
    def __init__(self, sk):
        self.shared_key = sk
        self.aes = AESCipher(self.shared_key)
    
    def run(self):
        s = socket.socket()
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        
        with conn:
            print('Got connection from', addr)
            
            # 2.1 receive public key from client
            msg1 = conn.recv(BUF)
            msg1_inner = self.aes.decrypt(msg1)
            pubkey = RSA.importKey(msg1_inner.encode('cp1252'))
            print('[B] recv: \n', msg1_inner)
            
            print('\n------ ROUND 2 ------')
            # 2.2 gen section key
            secc_key = ''.join(random.choices(string.ascii_letters + string.digits, k = 8))
            des = DESCipher(secc_key)
            
            print('[B] Session Key: \n', secc_key)
            rsa_enc = PKCS1_cipher.new(pubkey)
            secc_enc = rsa_enc.encrypt(bytes(secc_key.encode('utf8')))
            
            # 2.3 send section key
            msg2_inner = b64encode(secc_enc).decode('ascii')
            msg2 = self.aes.encrypt(msg2_inner)
            print('[B] send: \n', msg2)
            
            conn.sendall(msg2)
            
            # 4.1 receive random number NA
            msg3 = conn.recv(BUF)
            na = des.decrypt(msg3)
            print('[B] N_a = ', na)
            
            print('\n------ ROUND 4 ------')
            # 4.2 gen random number NB
            nb = ''.join(random.choices(string.digits, k = 20))
            print('[B] N_b = ', nb)
            
            msg4 = des.encrypt(na + nb)
            print('[B] send: ', msg4)
            conn.sendall(msg4)
            
            # 6.1 receive NB and check
            msg5 = conn.recv(BUF)
            nb_recv = des.decrypt(msg5)
            
            assert nb == nb_recv, 'nb != nb_recv'
            print('[B] Check N_b: OK')
            
            print('\n------ FINISH ------\n')

            while True:
                data = conn.recv(BUF)
                if not data:
                    break
                print('[B] recv: ', des.decrypt_zh(data))
                print()
                
                msg = input('[B] Your msg: ')
                en_msg = des.encrypt_zh(msg)
                print('[B] send: ', en_msg)
                conn.sendall(en_msg)



if __name__ == '__main__':
    shared_key = 'thisisasharekey'
    pid = os.fork()
    
    if pid == 0:
        time.sleep(2)
        client = Client(shared_key)
        client.run()     
    else:
        server = Server(shared_key)
        server.run()
