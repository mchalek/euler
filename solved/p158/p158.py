#!/usr/bin/python

# 26 possible terminal letters
# 26_C_13 ~= 10M max possible usage configs
# 2 possible cases of (lexicographic hit, no hit)
#  ~= 2^31 states, each an int; note that we won't ever use the full space of these, but (25 choose k) at each k

counts = [{0: (1,0)} for i in range(26)]

for n in range(1, 27):
    new_counts = [{} for i in range(26)]
    for j in range(26):
        # prev string ends in j

        for (used, (count_without, count_with)) in counts[j].iteritems():
            new_used = used ^ (1 << j)
            for i in range(j): # i comes before j lexicographically
                if used & (1 << i):
                    continue
                (existing_without, existing_with) = new_counts[i].get(new_used, (0, 0))
                new_counts[i][new_used] = (count_without + existing_without, count_with + existing_with)

            for i in range(j+1, 26): # i comes after j lexicographically, so add a hit
                if used & (1 << i):
                    continue
                (existing_without, existing_with) = new_counts[i].get(new_used, (0, 0))
                new_counts[i][new_used] = (existing_without, count_without + existing_with)
    
    yy = [sum([y[1] for y in x.values()]) for x in new_counts]
    print(yy)
    p_n = sum([y[1] for x in new_counts for y in x.values()])
    print(p_n)
    counts = new_counts
