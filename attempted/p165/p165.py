#!/usr/bin/python

from fraction import Fraction

class LineSegment:
    def __init__(self, p0, p1):
        (a, b) = p0
        (c, d) = p1

        self.a = a
        self.b = b
        self.c = c
        self.d = d

def check(l0, l1):
    a = l0.a
    b = l0.b
    c = l0.c
    d = l0.d

    e = l1.a
    f = l1.b
    g = l1.c
    h = l1.d

    num = (c-g)*(f-h) - (d-h)*(e-g)
    den = (b-d)*(e-g) - (a-c)*(f-h)

    if den == 0:
        return None # no intersection points

    t = float(num) / den

    #print('t == %s; tf == %s' % (str(t), str(tf)))

    if 0 < t < 1:
        if e == g:
            s = (t * (b-d) + (d-h)) / (f-h)
        else:
            s = (t * (a-c) + (c-g)) / (e-g)

        #print('s == %s; sf == %s' % (str(s), str(sf)))

        if 0 < s < 1:
            tf = Fraction(num, den)
            if e == g:
                sf = (tf * (b-d) + (d-h)) * Fraction(1, f-h)
            else:
                sf = (tf * (a-c) + (c-g)) * Fraction(1, e-g)

            #if 0 < sf < 1 and 0 < tf < 1:
            # compute intersection point and return
            #x = t*a + (1-t)*c
            #y = t*b + (1-t)*d 
            #return (x, y)

            xf = tf*a + (1-tf)*c
            yf = tf*b + (1-tf)*d 
            return (xf, yf)

    return None

def generate(N):
    items = []
    s4 = 290797

    for i in range(N):
        s1 = (s4*s4) % 50515093
        s2 = (s1*s1) % 50515093
        s3 = (s2*s2) % 50515093
        s4 = (s3*s3) % 50515093

        if i == 0:
            print('(%d, %d), (%d, %d)' % (s1 % 500, s2 % 500, s3 % 500, s4 % 500))

        segment = LineSegment((s1 % 500, s2 % 500), (s3 % 500, s4 % 500))
        items.append(segment)

    return items

segments = generate(5000)

p1 = LineSegment((27, 44), (12, 32))
p2 = LineSegment((46, 53), (17, 62))
p3 = LineSegment((46, 70), (22, 40))

print('check p1, p2: ' + str(check(p1, p2)))
print('check p2, p3: ' + str(check(p2, p3)))
print('check p1, p3: ' + str(check(p1, p3)))

intersections = set([])
num_raw = 0
for i in range(len(segments)):
    #if i % 100 == 0:
    #    print('working on segment %d' % i)
    a = segments[i]
    for j in range(1 + i, len(segments)):
        b = segments[j]

        x = check(a, b)

        if x is not None:
            (xf, yf) = x
            num_raw += 1
            print('%s\t%s' % (str(xf), str(yf)))
            intersections.add((xf.tuple(), yf.tuple()))

print('total number of intersections: %d' % num_raw)
print('number of unique intersections: %d' % len(intersections))

