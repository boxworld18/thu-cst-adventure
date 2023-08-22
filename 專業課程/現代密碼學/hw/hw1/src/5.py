C = "BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD"

if __name__ == '__main__':
    l = len(C)
    for key in range(26):
        str = ""
        for ch in list(C):
            str += chr((ord(ch) - 65 - key + 26) % 26 + 65)
        
        print(key, str)