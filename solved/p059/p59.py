import csv
import string

msg = csv.reader(open('cipher1.txt'), delimiter=',').next();
cipher = [int(i) for i in msg];
L = len(cipher);
key = list(cipher);
plaintext = list(cipher);

for a in range(97,123):
    for j in range(0,L,3):
        key[j] = a;
    for b in range(97,123):
        for j in range(1,L,3):
            key[j] = b;
        for c in range(97,123):
            for j in range(2,L,3):
                key[j] = c;

            spacecount = 0;
                
            for i, k in enumerate(cipher):
                plaintext[i] = k ^ key[i];
                if plaintext[i] == ord(' '):
                    spacecount += 1;
                    
            if spacecount > 200:
                print string.join([chr(i) for i in plaintext], '')
                print "Sum of ascii values: " + str(sum(plaintext));
                print "The password was: '" + string.join([chr(i) for i in key[0:3]], '') + "'"
