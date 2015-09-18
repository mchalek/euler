#!/usr/bin/python

# ant eventually reaches a repeated pattern of d_n_black
# run the ant out until it gets into the repeate phase, then
# identify the cycle properties and compute out the answer after
# 10^18 steps

def count(dn, N):
    max_cycle = 1000

    subset_index = -(2*max_cycle)

    preset = dn[:subset_index]
    subset = dn[subset_index:]

    def equals(shifted):
        for (index, item) in enumerate(shifted):
            if subset[index] != item:
                return False
        return True

    shift = 1
    test = subset[shift:]
    while not equals(test) and shift < len(subset):
        shift += 1
        test = subset[shift:]

    pre_sum = sum(preset)
    cycle_sum = sum(subset[:shift])

    num_cycles = (N - len(preset)) / shift
    tail = (N - len(preset)) % shift

    tail_sum = sum(subset[:tail])

    print('for total of %d steps' % N)
    print('cycle length is %d' % shift)
    print('pre_sum is %d' % pre_sum)
    print('cycle sum is %d' % cycle_sum)
    print('%d cycles' % num_cycles)
    print('%d tail items' % tail)
    print('tail sum: %d' % tail_sum)

    return pre_sum + (cycle_sum * num_cycles) + tail_sum

Z = 10**18
N = 2000
grid = [[0]*N for x in range(N)]

dn = []
n_black = 0

i = N / 2
j = N / 2

orientation = 0
num_steps = 0
while 0 <= i < N and 0 <= j <= N:
    current_color = grid[i][j]

    if current_color == 0:
        n_black += 1
        dn.append(1)
        grid[i][j] = 1
        orientation += 3
        orientation %= 4
    else:
        n_black -= 1
        dn.append(-1)
        grid[i][j] = 0
        orientation += 1
        orientation %= 4

    if orientation == 0:
        j += 1
    elif orientation == 1:
        i -= 1
    elif orientation == 2:
        j -= 1
    elif orientation == 3:
        i += 1
    else:
        raise

    num_steps += 1

# first do a test against the known value after num_steps steps
total_count = count(dn[1:20000], num_steps)

print('total count after %d steps: %d' % (num_steps, total_count))
print('expected total count: %d (%d)' % (n_black, sum(dn)))

# now do the real thing
print('total count after 10^18 steps: %d' % count(dn, Z))
