#!/usr/bin/python

def score(s, mins):
    ret = 0
    v = s.__iter__()
    for i in range(len(s)):
        ret += mins[v.next()]
    return ret

def inter(list1, list2, mins):
    s1 = set(list1)
    s2 = set(list2)
    si = s1.intersection(s2)
    ret = score(si, mins)

    return ret


mins = [0]*201

mins[0] = 0
mins[1] = 0

used = [[0],[1]]

N = 201

for i in range(2,N):
    currused = used[1] + used[i-1] + [1] + [i-1]
    if 1 == i-1:
        currmin = 1+mins[1]
    else:
        currmin = 1+mins[1]+mins[i-1]-inter(used[1], used[i-1], mins)

    print('testing i == %d' % i)
    for j in range(1,i):
        testused = used[j] + used[i-j] + [j] + [i-j]
        if j == i-j:
            testmin = 1+mins[j];
        else:
            testmin = 1+mins[j]+mins[i-j]-inter(used[j], used[i-j], mins)

        print('%d + %d: %d' % (j, i-j, testmin))
        if testmin < currmin:
            currmin = testmin
            currused = testused

    print('mins[%d] == %d' % (i, currmin))
    print('used:')
    print(currused)
    mins[i] = currmin
    used.append(currused)
