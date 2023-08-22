import re
import math

TEXT_SUB = "\
EMGLOSUDCGDNCUSWYSFHNSFCYKDPUMLWGYICOXYSIPJCK\
QPKUGKMGOLICHINCGACKSNISACYKZSCKXECJCKSHYSXCG\
OIDPKZCNKSHICGIWYGKKGKGOLDSILKGOIUSIGLEDSPWZU\
GFZCCNDGYYSFUSZCNXEOJNCGYEOWEUPXEZGACGNFGLKNS\
ACIGOIYCKXCJUCIUZCFZCCNDGYYSFEUEKUZCSOCFZCCNC\
IACZEJNCSHFZEJZEGMXCYHCJUMGKUCY"

TEXT_VIG = "\
KCCPKBGUFDPHQTYAVINRRTMVGRKDNBVFDETDGILTXRGUD\
DKOTFMBPVGEGLTGCKQRACQCWDNAWCRXIZAKFTLEWRPTYC\
QKYVXCHKFTPONCQQRHJVAJUWETMCMSPKQDYHJVDAHCTRL\
SVSKCGCZQQDZXGSFRLSWCWSJTBHAFSIASPRJAHKJRJUMV\
GKMITZHFPDISPZLVLGWTFPLKKEBDPGCEBSHCTJRWXBAFS\
PEZQNRWXCVYCGAONWDDKACKAWBBIKFTIOVKCGGHJVLNHI\
FFSQESVYCLACNVRWBBIREPBBVFEXOSCDYGZWPFDTKFQIY\
CWHJVLNHIQIBTKHJVNPIST"

TEXT_AFF = "\
KQEREJEBCPPCJCRKIEACUZBKRVPKRBCIBQCARBJCVFCUP\
KRIOFKPACUZQEPBKRXPEIIEABDKPBCPFCDCCAFIEABDKP\
BCPFEQPKAZBKRHAIBKAPCCIBURCCDKDCCJCIDFUIXPAFF\
ERBICZDFKABICBBENEFCUPJCVKABPCYDCCDPKBCOCPERK\
IVKSCPICBRKIJPKABI"

TEXT_UKN = "\
BNVSNSIHQCEELSSKKYERIFJKXUMBGYKAMQLJTYAVFBKVT\
DVBPVVRJYYLAOKYMPQSCGDLFSRLLPROYGESEBUUALRWXM\
MASAZLGLEDFJBZAVVPXWICGJXASCBYEHOSNMULKCEAHTQ\
OKMFLEBKFXLRRFDTZXCIWBJSICBGAWDVYDHAVFJXZIBKC\
GJIWEAHTTOEWTUHKRQVVRGZBXYIREMMASCSPBHLHJMBLR\
FFJELHWEYLWISTFVVYEJCMHYUYRUFSFMGESIGRLWALSWM\
NUHSIMYYITCCQPZSICEHBCCMZFEGVJYOCDEMMPGHVAAUM\
ELCMOEHVLTIPSUYILVGFLMVWDVYDBTHFRAYISYSGKVSUU\
HYHGGCKTMBLRX"

LETTER_FREQ = [0.082, 0.015, 0.028, 0.043, 0.127, 0.022,
               0.020, 0.061, 0.070, 0.002, 0.008, 0.040,
               0.024, 0.067, 0.075, 0.019, 0.001, 0.060,
               0.063, 0.091, 0.028, 0.010, 0.023, 0.001,
               0.020, 0.001]

AFF_A = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
AFF_INV = [1, 9, 21, 15, 3, 19, 7, 23, 11, 5, 17, 25]

class DecodeTool:
    def __init__(self, text = TEXT_SUB, lfreq = LETTER_FREQ, aff_a = AFF_A, aff_inv = AFF_INV):
        self.letter_freq = lfreq
        self.aff_a = aff_a
        self.aff_inv = aff_inv
        set(text)
        
    def set(self, text = TEXT_SUB):
        self.text = text
        self.converted = text
        self.len = len(text)
        self.key = [-1 for i in range(26)]
        self.freq = self.count_frequency_one(self.text)
        self.freq2 = self.count_frequency(self.text, 2)
        self.freq3 = self.count_frequency(self.text, 3)
            
    def count_frequency_one(self, text):
        tmp = [0] * 26
        for ch in list(text):
            tmp[ord(ch) - 65] += 1
        return tmp
    
    def count_frequency(self, text, len = 2):
        tmp_dict = {}
        for i in range(self.len - len + 1):
            str = text[i: i + len]
            if tmp_dict.get(str) == None:
                tmp_dict[str] = 1
            else:
                tmp_dict[str] += 1
        return sorted(tmp_dict.items(), key = lambda item: item[1], reverse = True)
            
    def print_frequency(self, len = 3, type_freq = True):
        ls = [sorted(self.freq).index(x) for x in self.freq]
        rk = 25
        while rk >= 0:
            for i in range(26):
                if (ls[i] == rk):
                    if type_freq:
                        print("{}: {:10.5}%".format(chr(i + 65), self.freq[i] / self.len * 100))
                    else:
                        print("{}: {:3}".format(chr(i + 65), self.freq[i]))
            rk -= 1
        
        if len >= 2:
            print(self.freq2)
        
        if len >= 3:
            print(self.freq3)
    
    def find_substring_pos(self, sub):
        return [m.start() for m in re.finditer(sub, self.text)]
       
    def mark(self, ch1, ch2):
        self.key[ord(ch1) - 65] = ord(ch2) - 65
        
    def convert_text(self):
        str = ""
        for ch in list(self.text):
            if self.key[ord(ch) - 65] == -1:
                str += " "
            else:
                str += chr(self.key[ord(ch) - 65] + 65)
                
        self.converted = str
        return str
    
    def convert_with_key(self, key):
        str = ""
        for i in range(self.len):
            str += chr((ord(self.text[i]) - 65 + 26 - key[i % len(key)]) % 26 + 65)
        
        self.converted = str
        return str.lower()

    def convert_with_affine_key(self, inv, b):
        str = ""
        for i in range(self.len):
            str += chr((inv * (ord(self.text[i]) - 65 - b)) % 26 + 65)
        
        self.converted = str
        return str.lower()
        
    def print_text(self):
        self.wpl = 70
        for i in range(0, self.len, self.wpl):
            print(self.text[i: i + self.wpl])
            print(self.converted[i: i + self.wpl])
         
    def kasiski(self):
        print("===== Kasiski Test =====")
        print(self.freq3)
        print("Use {} for searching.".format(self.freq3[0]))
        tar_str = self.freq3[0][0]
        res = self.find_substring_pos(tar_str)
        ls = [i - res[0] for i in res]
        key_len = math.gcd(*ls)
        
        print("Position: {}".format(res))
        print("Possible key len: {}".format(key_len))
        print("========================")
        
        return key_len

    def coincidence_index(self, text, key_len = 2):
        res = []
        text_len = len(text)
        for st_len in range(key_len):
            tmp_text = ""
            for i in range(st_len, text_len, key_len):
                tmp_text += text[i]
            freq_ls = self.count_frequency_one(tmp_text)
            
            sum = 0
            for i in range(0, 26):
                sum += (freq_ls[i] / len(tmp_text))**2
            
            # print(sum)
            key_test = []
            
            for key_shift in range(26):
                mg = 0
                for i in range(0, 26):
                    new_letter = (i - key_shift + 26) % 26
                    mg += self.letter_freq[new_letter] * freq_ls[i] / len(tmp_text)
                key_test.append(round(mg, 3))
            
            # print(key_test)
            tar_key = key_test.index(max(key_test))
            print("key {} is {:3} with Mg = {}.".format(st_len, tar_key, max(key_test)))
            res.append(tar_key)
            
        return res

    # E(ch2) = ch1, or D(ch1) = ch2
    def match_affine(self, ch1, ch2):
        y = ord(ch1) - 65
        x = ord(ch2) - 65
        print(x, y)
        for idx in range(len(self.aff_a)):
            a = self.aff_a[idx]
            inv = self.aff_inv[idx]
            b = (y - a * x) % 26
            print("a = {:2}, b = {:2}.".format(a, b))
            print("decrypte with d(y) = {:2}(y - {:2}) % 26".format(a, b, inv, b))
            res = self.convert_with_affine_key(inv, b)
            print(res)
    
def solve_sub_cipher(text):
    tool = DecodeTool()
    tool.set(text)
    tool.print_frequency()
    tool.mark('F', 'W')
    tool.mark('C', 'E')
    tool.mark('Z', 'H')
    tool.mark('N', 'L')
    tool.mark('U', 'T')
    tool.mark('S', 'O')
    tool.mark('O', 'N')
    
    tool.mark('G', 'A')
    tool.mark('K', 'S')
    tool.mark('Y', 'R')
    
    tool.mark('W', 'G')
    tool.mark('H', 'F')
    tool.mark('I', 'D')
    tool.mark('D', 'B')
    tool.mark('P', 'U')
    
    tool.mark('E', 'I')
    tool.mark('M', 'M')
    tool.mark('L', 'Y')
    
    tool.mark('J', 'C')
    tool.mark('X', 'P')
    tool.mark('A', 'V')
    tool.mark('Q', 'J')
    
    tool.convert_text()
    tool.print_text()
 
def solve_vig_cipher(text, key_len = -1):
    tool = DecodeTool()
    tool.set(text)
    if key_len == -1:
        key_len = tool.kasiski()
    key = tool.coincidence_index(text, key_len)
    res = tool.convert_with_key(key)
    print(res)
    # tool.print_text()
    
def solve_aff_cipher(text):
    tool = DecodeTool()
    tool.set(text)
    tool.print_frequency(1, False)
    tool.match_affine('C', 'E')
    
if __name__ == '__main__':
    # solve problem 21(a)
    solve_sub_cipher(TEXT_SUB)
    
    # solve problem 21(b)
    solve_vig_cipher(TEXT_VIG)
    
    # solve problem 21(c)
    solve_aff_cipher(TEXT_AFF)
    
    # solve problem 21(d)
    solve_vig_cipher(TEXT_UKN, 6)