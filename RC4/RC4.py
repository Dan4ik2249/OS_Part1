import sys

def KSA(key, S):
    string = len(key)
    j = 0
    
    for i in range(256):
        S[i] = i

    for i in range(256):
        j = (j + S[i] + int(key[i % string])) % 256
        S[i], S[j] = S[j], S[i]
    
    return 0

def PRGA(S, plaintext, ciphertext):
    i = j = 0
    string = len(plaintext)
    rnd = []
    res = []
    for n in range(string):
        i = (i + 1) % 256
        j = (j + S[i]) % 256

        S[i], S[j] = S[j], S[i]
        rnd = S[(S[i] + S[j]) % 256]

        res.append(chr((rnd) ^ (plaintext[n])))
    ciphertext = "".join(res)

    return ciphertext

def RC4(key, plaintext, ciphertext):
    S = list(range(256))
    KSA(key, S)
    PRGA(S, plaintext, ciphertext)

    return 0

def main():
    infile = sys.argv[2]
    outfile = sys.argv[3]
    ciphertext = list(range(256))
        
    with open(infile, 'rb') as fd1:
       buffer = fd1.read()
    
    S = list(range(256))
    KSA(sys.argv[1], S)
    ciphertext = PRGA(S, buffer, ciphertext)
    
    with open(outfile, 'w', encoding = 'utf-8') as fd2:
         fd2.write(ciphertext)
    
if __name__ == '__main__':
    maint(
