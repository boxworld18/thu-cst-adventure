import numpy as np

TEXT = "\
LMQETXYEAGTXCTUIEWNCTXLZEWUAISPZYVAPEWLMGQWYA\
XFTCJMSQCADAGTXLMDXNXSNPJQSYVAPRIQSMHNOCVAXFV"

WORD_ALL = ["TH", "HE", "IN", "ER", "AN",
            "RE", "DE", "ON", "ES", "ST",
            "EN", "AT", "TO", "NT", "HA",
            "ND", "OU", "EA", "NG", "AS",
            "OR", "TI", "IS", "ET", "IT",
            "AR", "TE", "SE", "HI", "OF"]

WORD_5 = ["TH", "HE", "IN", "ER", "AN"]

class HillCipher:
    def __init__(self, text = TEXT, word2 = WORD_5):
        self.len = len(text)
        self.text = text
        self.word2 = word2
    
    def exgcd(self, a, b):
        if b == 0:
            return 1, 0, a
        else:
            x, y, q = self.exgcd(b, a % b)
            x, y = y, (x - (a // b) * y)
            return x, y, q
        
    def mod_rev(self, a, p):
        x, y, q = self.exgcd(a, p)
        if q == 1:
            return (x + p) % p
        else:
            return None
        
    def count_freq(self, cut_len = 2):
        tmp_dict = {}
        for st in range(0, self.len, cut_len):
            str = self.text[st: st + cut_len]
            if tmp_dict.get(str) == None:
                tmp_dict[str] = 1
            else:
                tmp_dict[str] += 1
        return sorted(tmp_dict.items(), key = lambda item: item[1], reverse = True)
    
    def matrix_det(self, mat):
        mat = mat.reshape(2, 2)
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]
    
    def matrix_inv(self, mat):
        mat = mat.reshape(2, 2)
        det = self.matrix_det(mat)
        det_inv = self.mod_rev(det, 26)
        if det_inv is None:
            return None
        tmp_mat = np.array([mat[1][1], -mat[0][1],
                          -mat[1][0], mat[0][0]]).reshape(2, 2)
        tmp_mat = tmp_mat * det_inv
        return tmp_mat % 26
    
    def find_matrix(self, src1, src2, dst1, dst2):
        x00 = ord(src1[0]) - 65
        x01 = ord(src1[1]) - 65
        x10 = ord(src2[0]) - 65
        x11 = ord(src2[1]) - 65
        y00 = ord(dst1[0]) - 65
        y01 = ord(dst1[1]) - 65
        y10 = ord(dst2[0]) - 65
        y11 = ord(dst2[1]) - 65
        mat_x = np.array([x00, x01, x10, x11]).reshape(2, 2)
        mat_y = np.array([y00, y01, y10, y11]).reshape(2, 2)
        inv_x = self.matrix_inv(mat_x)
        if inv_x is None:
            return None
        mat_k = np.dot(inv_x, mat_y) % 26
        return mat_k
    
    def decode(self, mat, cut_len = 2):
        str = ""
        for st in range(0, self.len, cut_len):
            src = self.text[st: st + cut_len]
            x = np.array([ord(src[0]) - 65, ord(src[1]) - 65]).reshape(1, 2)
            res = np.dot(x, mat) % 26
            str += chr(res[0][0] + 65)
            str += chr(res[0][1] + 65)
            
        return str
    
    def encode(self, txt, mat, cut_len = 2):
        str = ""
        for st in range(0, len(txt), cut_len):
            src = txt[st: st + cut_len]
            x = np.array([ord(src[0]) - 65, ord(src[1]) - 65]).reshape(1, 2)
            res = np.dot(x, mat) % 26
            str += chr(res[0][0] + 65)
            str += chr(res[0][1] + 65)
            
        return str
    
    def run(self):
        self.freq = self.count_freq()
        src1 = self.freq[0][0]
        src2 = self.freq[1][0]
        
        for dst1 in self.word2:
            for dst2 in self.word2:
                mat = self.find_matrix(src1, src2, dst1, dst2)
                if mat is None:
                    continue
                inv = self.matrix_inv(mat)
                if inv is None:
                    continue
                
                str = self.decode(mat)
                print("K:", inv.reshape(1, 4), "inv(K):", mat.reshape(1,4), src1, "<-", dst1, src2, "<-", dst2, str)
            
if __name__ == '__main__':
    hc = HillCipher()
    hc.run()
    pass