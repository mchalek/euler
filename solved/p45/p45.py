#!/usr/bin/python
from math import sqrt, floor

nout = 0

t = 0
while True:
    t += 1
    z = t*(t+1)/2
    
    pix = (1. + sqrt(1 + 24*z))/6.
    if pix != floor(pix):
        continue

    hix = (1. + sqrt(1 + 8*z))/4.
    if hix != floor(hix):
        continue

    p = pix*(3*pix-1)/2
    h = hix*(2*hix-1)
    print 'tri %d %d   pen %d %d   hex %d %d' % (t, z, pix, p, hix, h)

    if t > 285:
        break
    
