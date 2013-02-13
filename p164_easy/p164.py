#!/usr/bin/python

# need transitions

current_count_leading2dig = [0]*100
count_trailing_2dig = [0]*100

for i in range(1000):
    a = i % 10
    b = (i / 10) % 10
    c = (i / 100) % 10

    if a + b + c < 9:
        count_trailing_2dig[b*10+a] += 1
        current_count_leading_2dig[c*10+b] += 1

        print('%d is valid' % i)


for i in range(100):
    print('%d 3-dig valid start with %d' % (current_count_leading_2dig[i], i))
    print('%d 
