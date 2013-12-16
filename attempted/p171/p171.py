#!/usr/bin/python

digsquares = [i*i for i in range(10)]
maxtest = 20*81

allsquares = []
i = 0
i2 = 0
while i2 < maxtest:
    i += 1
    i2 = i*i
    allsquares.append(i2)


print digsquares
print allsquares

for i in range(len(allsquares)):
    
