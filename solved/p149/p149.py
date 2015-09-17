#!/usr/bin/python

def max_subsequence(seq):
    mx = 0 # assume empty subsequence is permitted

    best_running = 0
    for x in seq:
        best_running = max(best_running + x, x, 0)
        
        if best_running > mx:
            mx = best_running
    return best_running

def extract_column(matrix, index):
    col = []
    for row in matrix:
        col.append(row[index])

    return col

def extract_diagonal(matrix, index):
    if index < 0:
        i = -index
        j = 0
    else:
        i = 0
        j = index

    diag = []
    while j < len(matrix) and i < len(matrix):
        diag.append(matrix[i][j])
        i += 1
        j += 1

    return diag

def extract_anti_diagonal(matrix, index):
    if index < 0:
        i = 0
        j = len(matrix)-1-index
    else:
        i = index
        j = len(matrix)-1

    diag = []
    while i < len(matrix) and j >= 0:
        diag.append(matrix[i][j])

        i += 1
        j -= 1

    return diag

def find_best(matrix):
    mx = max_subsequence(matrix[0])
    for i in range(1, len(matrix)):
        mx = max(mx, max_subsequence(matrix[i]))

    for i in range(len(matrix)):
        col = extract_column(matrix, i)
        mx = max(mx, max_subsequence(col))

        diag = extract_diagonal(matrix, i)
        mx = max(mx, max_subsequence(diag))

        anti_diag = extract_anti_diagonal(matrix, i)
        mx = max(mx, max_subsequence(anti_diag))

    print('max is: ' + str(mx))

def generate_matrix():
    s = [0]
    matrix = []
    row = []
    for k in range(1, 56):
        sk = ((100003 - 200003*k + 300007*(k**3)) % 1000000) - 500000

        if k == 10:
            print('s_10 == %d' % sk)

        s.append(sk)
        row.append(sk)

    for k in range(56, 4000001):
        sk = ((s[k-24] + s[k-55] + 1000000) % 1000000) - 500000

        if k == 100:
            print('s_100 == %d' % sk)

        s.append(sk)
        row.append(sk)

        if len(row) == 2000:
            matrix.append(row)
            row = []

    return matrix

example = [[-2,5,3,2],[9,-6,5,1],[3,2,7,3],[-1,8,-4,8]]
find_best(example)

matrix = generate_matrix()
find_best(matrix)
