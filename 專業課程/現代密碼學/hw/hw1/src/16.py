C = "ETEGENLMDNTNEOORDAHATECOESAHLRMI"
PI = [4, 1, 6, 2, 7, 3, 8, 5]

if __name__ == '__main__':
    cipher_len = len(PI)
    str_len = len(C)
    
    pi1 = []
    for j in range(cipher_len):
        for i in range(cipher_len):
            if PI[i] == j + 1:
                pi1.append(i + 1)
                
    pi0 = []
    for j in range(cipher_len):
        for i in range(cipher_len):
            if pi1[i] == j + 1:
                pi0.append(i + 1)
                   
            
    for le in range(0, str_len, cipher_len):
        str = ""
        chip = list(C[le: le + cipher_len])
        for i in range(cipher_len):
            str += chip[pi0[i] - 1]
        
        print(str.lower(), end = " ")
    
    print()