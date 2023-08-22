import numpy as np
import itertools
import string
import time
from tqdm import tqdm

# Enigma Constructure
ROTOR = ["EKMFLGDQVZNTOWYHXUSPAIBRCJ",
         "AJDKSIRUXBLHWTMCQGZNPYFVOE",
         "BDFHJLCPRTXVZNYEIWGAKMUSQO",
         "ESOVPZJAYQUIRHXLNFTGKDCMWB",
         "VZBRGITYUPSDNHLXAWMJQOFECK"]

NOTCH = ["Q", "E", "V", "J", "Z"]

REFLECTOR = ["EJMZALYXVBWFCRQUONTSPIKHGD",
             "YRUHQSLDPXNGOKMIEBFZCWVJAT",
             "FVPJIAOYEDRZXWGCTKUQSBNMHL"]

# Target Message
TAR_MSG = ["ELCONWDIAPKSZHFBQTJYRGVXMU",
           "MRWJFDVSQEXUCONHBIPLTGAYZK",
           "WADFRPOLNTVCHMYBJQIGEUSKZX"]

# Basic Setting
BASIC_ROTOR_ORDER = [2, 3, 1]       # from 1 to 5 (I to V)
BASIC_RING_SETTING = list("DES")
BASIC_INIT_POS = list("AAA")
BASIC_REFLECTOR = 'B'               # A - C, M3 only use B
BASIC_PLUG_SETTING = ""           # eg. "AB CD EF GH IJ"

#              01234567890123456
KNOWN_TEXT =  "ASTWBKDJXSAXQFCJT"
CIPHER_TEXT = "STWTJDJXSAQBJQJOD"

# Enigma Simulator
class Enigma:
    def __init__(self, 
                 rotor_order = BASIC_ROTOR_ORDER, 
                 ring_setting = BASIC_RING_SETTING, 
                 init_pos = BASIC_INIT_POS,
                 reflector_order = BASIC_REFLECTOR,
                 plug_setting = BASIC_PLUG_SETTING) -> None:
        self.basic_rotor_order = rotor_order
        self.rotor_order = [i - 1 for i in rotor_order]
        self.ring_setting = ring_setting
        self.init_pos = init_pos
        self.ref_order = ord(reflector_order) - 65
        self.plug_setting = plug_setting.split(" ")
        self.reset()
        
    def set(self, 
            rotor_order = BASIC_ROTOR_ORDER, 
            ring_setting = BASIC_RING_SETTING, 
            init_pos = BASIC_INIT_POS,
            reflector_order = BASIC_REFLECTOR,
            plug_setting = BASIC_PLUG_SETTING) -> None:
        self.rotor_order = [i - 1 for i in rotor_order]
        self.basic_rotor_order = rotor_order
        self.ring_setting = ring_setting
        self.init_pos = init_pos
        self.ref_order = ord(reflector_order) - 65
        self.plug_setting = plug_setting.split(" ")
        self.reset()
    
    def reset(self):
        self.dbl_step = 0;
        self.rotor = ["", "", ""]
        self.pos = [ord(ch) - 65 for ch in self.init_pos]
        self.rotor_sh = np.zeros((3, 26), dtype = int)
        self.reflector = REFLECTOR[self.ref_order]
        self.set_rotor()
    
    # rotor setting
    def set_rotor(self):
        for idx in range(3):
            order = self.rotor_order[idx]
            converted = np.zeros(0)
            
            # calculate wiring
            ls = list(ROTOR[order])    
            cnt = 0            
            for ch in ls:
                tar = (ord(ch) - 65 - cnt + 26) % 26
                converted = np.append(converted, tar)
                cnt += 1
                if cnt >= len(ls):
                    break
            
            self.rotor_sh[idx] = converted
            
            cnt = ord(self.ring_setting[idx]) - 65
            self.rotate(idx, cnt)
            self.change_rotor(idx)
            
            stp = ord(self.init_pos[idx]) - 65
            self.shift(idx, stp)
             
    def rotate(self, idx, num = 1):
        a, b = np.split(self.rotor_sh[idx], [26 - num])
        self.rotor_sh[idx] = np.append(b, a)
        
    def change_rotor(self, idx):
        str = ""
        for i in range(26):
            str += chr(65 + (i + self.rotor_sh[idx][i]) % 26)
        self.rotor[idx] = str
    
    # Settings        
    def print_setting(self):
        # str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        # print([str, str, str])
        # print(self.rotor)
        print(self.basic_rotor_order)
        print(self.init_pos)
        print(self.ring_setting)
     
    # Rotor simulation   
    def press_one(self):
        self.pos[2] = (self.pos[2] + 1) % 26
        self.shift(2)
        if self.pos[2] == ord(NOTCH[self.rotor_order[2]]) + 1 - 65 or self.dbl_step == 1:
            self.pos[1] = (self.pos[1] + 1) % 26
            self.shift(1)
            # special structure: double step of middle rotor
            self.dbl_step = 0
            if self.pos[1] == ord(NOTCH[self.rotor_order[1]]) - 65:
                self.dbl_step = 1
                
            if self.pos[1] == ord(NOTCH[self.rotor_order[1]]) + 1 - 65:
                self.pos[0] = (self.pos[0] + 1) % 26
                self.shift(0)
        # print([chr(i + 65) for i in self.pos])
    
    def shift(self, idx, num = 1):
        str = ""
        for i in range(26):
            str += chr(65 + (ord(self.rotor[idx][i]) - 65 - num) % 26)
        self.rotor[idx] = str[num:] + str[0: num]
        
    # Functions for encryption
    def find(self, idx, ch):
        och = ord(ch)
        return self.rotor[idx][och - 65]
    
    def find_r(self, idx, ch):
        for i in range(26):
            if self.rotor[idx][i] == ch:
                return chr(65 + i)
             
    def reflect(self, ch):
        return self.reflector[ord(ch) - 65]
    
    def plug(self, ch):
        if self.plug_setting[0] == "":
            return ch
        
        for ps in self.plug_setting:
            if ch == ps[0]:
                return ps[1]
            if ch == ps[1]:
                return ps[0]
        return ch
    
    def encrypte(self, ch1):
        ch1 = ch1.upper()
        self.press_one()
        # self.print_setting()
        # ch1 = self.plug(ch1)
        ch2 = self.find(2, ch1)
        ch3 = self.find(1, ch2)
        ch4 = self.find(0, ch3)
        ch5 = self.reflect(ch4)
        ch6 = self.find_r(0, ch5)
        ch7 = self.find_r(1, ch6)
        ch8 = self.find_r(2, ch7)
        # ch9 = self.plug(ch8)
        # print(ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9)
        return ch8
    
    def encrypte_str(self, str: str):
        res = ""
        for ch in list(str):
            if ch.isalpha():
                res += self.encrypte(ch)
        return res
    
class Bomba:
    def __init__(self, tar = TAR_MSG, kmsg = KNOWN_TEXT, cmsg = CIPHER_TEXT):
        tmp = [list(content) for content in tar]
        self.target = [self.find_circle(tmp[0]),
                       self.find_circle(tmp[1]),
                       self.find_circle(tmp[2])]
        
        self.rings = []
        self.tmp_rings = []
        self.cur_ring = []
        self.known_msg = kmsg
        self.cipher_msg = cmsg
        self.find_ring(self.known_msg, self.cipher_msg)
        self.rings = sorted(self.rings, key = lambda x: len(x))

    def dfs(self, st, src, vis, msg1, msg2):
        msg_len = len(msg1)
        for i in range(msg_len):
            if vis[i] == False:
                if msg1[i] == src:
                    nxt = msg2[i]
                elif msg2[i] == src:
                    nxt = msg1[i]
                else:
                    continue
                
                vis[i] = True
                self.cur_ring.append(i)
                
                if nxt == st:
                    self.tmp_rings.append(self.cur_ring.copy())    
                
                if len(self.cur_ring) <= 7:
                    self.dfs(st, nxt, vis, msg1, msg2)
                    
                self.cur_ring.pop(-1)
                vis[i] = False
        pass
    
    def find_ring(self, msg1, msg2):
        msg_len = len(msg1)
        vis = [False] * msg_len
        for i in range(msg_len):
            st = msg1[i]
            nxt = msg2[i]
            self.tmp_rings = []
            vis[i] = True
            self.cur_ring.append(i)
            self.dfs(st, nxt, vis, msg1, msg2)
            self.cur_ring.pop(-1)
            vis[i] = False
            
            if (len(self.tmp_rings) > len(self.rings)):
                self.rings = self.tmp_rings.copy()
            
            if i == 0:
                break
    
    def find_circle(self, ls):
        vis = [False for _ in range(26)]
        rings = []
        for i in range(26):
            if vis[i] == False:
                cnt = 1
                vis[i] = True
                nxt = ord(ls[i]) - 65
                while vis[nxt] == False:
                    vis[nxt] = True
                    nxt = ord(ls[nxt]) - 65
                    cnt += 1
                rings.append(cnt)
        rings.sort()
        return rings
        
    def tuning(self):
        st_time = time.time()
        possible_key = []

        self.ro = [item for item in itertools.permutations([1, 2, 3])]
        self.ro_len = len(self.ro)
        ls = [string.printable[36: 62]] * self.ro_len
        
        for combo in itertools.product(string.printable[36: 62], repeat = 3):
            possible_key.append([''.join(combo), ls.copy()])
        
        # possible_key = [["AAA", ls.copy()], ["DES", ls.copy()]]
        # self.rings = [[4, 7, 11]]
        enigma = Enigma()
        
        for ring_cnt in range(len(self.rings)):
            print("Testing ring #{:2}.".format(ring_cnt))
            
            for item in tqdm(possible_key): 
                it = item.copy()
                key, pos_letter = item 
                
                flag = False          
                for idx in range(self.ro_len):
                    tar_ro = self.ro[idx] 
                    tar_chr = pos_letter[idx]
                        
                    new_chr = ""
                    for st in list(tar_chr):
                        ch = st
                        for rt in self.rings[ring_cnt]:
                            enigma.set(tar_ro, key)
                            for _ in range(rt):
                                enigma.press_one()
                            ch = enigma.encrypte(ch)
                    
                        if ch == st:
                            flag = True
                            new_chr += st
                     
                    pos_letter[idx] = new_chr
                  
                if flag == False:
                    possible_key.remove(it)       
                             
            
        
        print("=================================")    
        print("Time used: {:.5}s".format(time.time() - st_time))
        print("Result:\n", possible_key)
        print("=================================") 
    
    def hack(self):
        ls = list(itertools.permutations([1, 2, 3]))
        progress = tqdm(total = 6 * 26 * 26 * 26)
        for rotor_order in ls:
            for i in string.printable[36: 62]:
                print("testing", i , "as the first rotor's init")
                for j in string.printable[36: 62]:
                    for k in string.printable[36: 62]:
                        self.test(rotor_order, [i, j, k])
                        progress.update(1)
    
    def test(self, ro, sr):
        enigma = Enigma(ro, sr)
        ls1 = list(" " * 26)
        ls2 = list(" " * 26)
        ls3 = list(" " * 26)
        for ch in string.printable[36: 62]:
            str = ch * 6
            res = enigma.encrypte_str(str)
            enigma.set(ro, sr)
            ls1[ord(res[0]) - 65] = res[3]
            ls2[ord(res[1]) - 65] = res[4]
            ls3[ord(res[2]) - 65] = res[5]
            
        res = [self.find_circle(ls1),
               self.find_circle(ls2),
               self.find_circle(ls3)]
        
        if res == self.target:
            enigma.print_setting()
            
        return res

def print_result_in_grp(res, cnv = 0, grp = 3):
    res = res.lower() if cnv == 1 else res
    strlen = len(res)
    for i in range(0, strlen, 5):
        if i + 5 < strlen:
            print(res[i: i + 5], end = " ")
        else:
            print(res[i:])
        if i // 5 % grp == grp - 1:
            print()
          
if __name__ == '__main__':
    bomba = Bomba()
    # task 1
    bomba.hack()
    # task 2
    bomba.tuning()