import csv
import time

tstart = time.clock()

words = csv.reader(open('words.txt'), delimiter=',').next();

istri = [0 for i in range(500)];
n = 1;
x = 1;
while x < 500:
    istri[x] = 1;
    n += 1;
    x = n*(n+1)/2;
    
baseASCII = ord('A') - 1;
ntri = 0;
for w in words:
    val = sum([ord(x) - baseASCII for x in w]);
    ntri += istri[val]
        
print "{0} triangle words found.".format(ntri)

print "execution time: {0}".format(time.clock() - tstart)