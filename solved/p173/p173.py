#!/usr/bin/python
num_tiles = 1000000

counts = [0]*(1+num_tiles)

# loop over the size of the inside square hole,
# and then loop over all ways of surrounding that hole.
# stop when the inside hole is big enough that the max tiles
# available cannot cover the inside hole
inside = 1
while True:
    outside = inside + 2
    blocks = 4*(outside-1)

    if blocks > num_tiles:
        break

    while blocks <= num_tiles:
        counts[blocks] += 1

        outside += 2
        blocks += 4*(outside-1)

    inside += 1

print('ways with 32 tiles: %d' % counts[32])
print('ways with up to 100 tiles: %d' % sum(counts[:101]))
print('ways with up to 1000000 tiles: %d' % sum(counts[:1000001]))
