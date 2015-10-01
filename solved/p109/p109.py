raw_scores = range(1,21)

singles = [(x, 'S%d'%x) for x in (raw_scores + [25])]
doubles = [(2*x, 'D%d'%x) for x in (raw_scores + [25])]
triples = [(3*x, 'T%d'%x) for x in raw_scores]

all_items = singles + doubles + triples

min_score = 0
max_score = 99

checkouts = set([])
for (d0, ds) in doubles:
    # d0 is final item
    # do single-dart checkout
    if min_score <= d0 <= max_score:
        checkout = tuple([ds, 'x', 'x'])
        checkouts.add(checkout)

    for (y, ys) in all_items:
        score = d0 + y
        if min_score <= score <= max_score:
            checkout = tuple([ys, ds, 'x'])
            checkouts.add(checkout)

        for (z, zs) in all_items:
            score = d0 + y + z
            if min_score <= score <= max_score:
                pair = [ys, zs]
                pair.sort()
                checkout = tuple(pair + [ds])
                checkouts.add(checkout)

print(len(checkouts))
