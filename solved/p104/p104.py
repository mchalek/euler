def pan_right(x):
    x %= 1000000000
    mask = 0
    while x != 0:
        digit = x % 10
        bit = 1 << digit
        if (mask & bit) != 0:
            break
        mask |= bit
        x /= 10

    return mask == 0x3fe

def pan_left(x):
    while x > 1000000000:
        x /= 10
    return pan_right(x)

def next(a):
    return [a[1], a[0] + a[1]]

def find():
    a = [1,1]
    
    i = 2
    stop = False
    while not stop:
        a = next(a)
        F = a[1]
        i += 1

        if pan_right(F):
            print('pandigital right found at F_%d' % i)
            stop = pan_left(F)
    
    print('pandigital left / right found at F_%d' % i)

find()
