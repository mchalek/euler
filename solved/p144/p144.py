#!/usr/bin/python

import math
import sys

def compute_intersection(m, b):
    # return 2 (x, y) coordinates at which the line y=mx + b intercepts the ellipse
    # 4x^2 + y^2 == 100

    result = []
    def package(x):
        if -5 <= x <= 5:
            y00 = math.sqrt(100-4*x**2)
            diff = math.fabs(y00 - m*x - b)
            if diff < 1e-10:
                result.append((x, y00))

            y01 = -math.sqrt(100-4*x**2)
            diff = math.fabs(y01 - m*x - b)
            if diff < 1e-10:
                result.append((x, y01))

    coeffs = [4+m**2, 2*m*b, b**2 - 100]
    d = coeffs[1]**2 - 4*coeffs[0]*coeffs[2]

    x0 = (-coeffs[1] + math.sqrt(d)) / (2*coeffs[0])
    package(x0)

    x1 = (-coeffs[1] - math.sqrt(d)) / (2*coeffs[0])
    package(x1)

    return result

def tangent_line(x, y):
    m = -4*x/y
    b = y - m*x

    return (m, b)

def tangent_angle(x, y):
    (m, b) = tangent_line(x, y)

    if y > 0:
        return math.atan(m) + math.pi
    else:
        return math.atan(m)

def rotate(points, theta):
    ct = math.cos(theta)
    st = math.sin(theta)

    return [(ct*x - st*y, st*x + ct*y) for (x, y) in points]

def slope(pair):
    (x0, y0) = pair[0]
    (x1, y1) = pair[1]

    return (y1-y0)/(x1-x0)

def dist2(a, b):
    (x0, y0) = a
    (x1, y1) = b

    return (x0-x1)**2 + (y0-y1)**2

def next_point(prev_points):
    (x1, y1) = prev_points[1]

    theta = tangent_angle(x1, y1)

    rp = rotate(prev_points, -theta)

    rotated_slope = slope(rp)

    if rp[1][0] > rp[0][0]:
        fake_next_rx = rp[1][0] + 1
    else:
        fake_next_rx = rp[1][0] - 1

    fake_next_ry = -rotated_slope * (fake_next_rx - rp[1][0]) + rp[1][1]
    fake_next_point = (fake_next_rx, fake_next_ry)

    fake_next_pair = rotate([rp[1], fake_next_point], theta)

    next_slope = slope(fake_next_pair)
    next_intercept = fake_next_pair[0][1] - next_slope * fake_next_pair[0][0]

    isect = compute_intersection(next_slope, next_intercept)

    new_point = [p for p in isect if dist2(p, fake_next_pair[0]) > 1e-4]

    if len(new_point) != 1:
        print('FAILURE: ' + str(new_point))
        sys.exit(1)

    return new_point[0]

points = [(0, 10.1), (1.4, -9.6)]
writer = open('test.csv', 'w')
writer.write('%g,%g\n' % points[0])
writer.write('%g,%g\n' % points[1])

num_refl = 0
quit = False
while not quit:
    np = next_point(points)

    num_refl += 1

    if -0.01 <= np[0] <= 0.01 and np[1] > 0:
        quit = True
        print('Exit at point (%g, %g) after %d reflections' % (np[0], np[1], num_refl))

    writer.write('%g,%g\n' % np)

    points = [points[1], np]

writer.close()
