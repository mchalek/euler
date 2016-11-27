# Strategy:
# - First compute D == LCM(2, 3, ..., 80) so that we can use (big-) integer sums
# - Next discard terms that cannot be present because they cannot be made
#   congruent to the target sum by other available terms:
#   if z_0 + z_1 + ... + z_k == D/2, then:
#     z_0 + z_1 + ... + z_k mod m == D / 2 mod m, for any m
#   For simplicity, we just take a bunch of m for which D / 2 mod m == 0.  We
#   find all of the terms z_i == D / n_i^2, n_i between 2 and 80, for which
#   z_i mod m != 0, and then ask whether it's possible to form a unique sum of
#   these in order to make 0.  If not, discard all of the z_i; if so, keep them
#   all (even though it's possible that some are invalid).
# - Finally, from this reduced set of terms (we get down to 34), exhaustively
#   search for solutions.  We use a meet-in-middle approach to speed things up,
#   constructing 2 tables of ~ 2^17 elements each and then finding pairings
#   that sum to the target.

def gcd(a, b):
    if a == b:
        return a

    if a > b:
        return gcd(b, a)

    r = b % a

    if r == 0:
        return a

    return gcd(r, a)

def lcm(a, b):
    return a * b / gcd(a, b)

def get_denominator(N):
    den = 1
    for n in range(2, 1 + N):
        den = lcm(den, n*n)

    return den

def update_accessible(x, p, accessible):
    assert(x < p)

    new_accessible = {a: b for (a, b) in accessible.items()}
    new_accessible.setdefault(x, 0)
    new_accessible[x] += 1

    for (value, count) in accessible.items():
        w = (value + x) % p
        new_accessible.setdefault(w, 0)
        new_accessible[w] += count

    return new_accessible

def can_make_zero(counts):
    p = len(counts)
    accessible = {}

    for (k, count) in enumerate(counts):
        if not k or not count:
            continue

        for z in range(count):
            accessible = update_accessible(k, p, accessible)

    return 0 in accessible

def reduce_candidate_squares(numerator, denominator, N):
    pp = []
    # Can check target mod p for any p, even those bigger than N.
    # Stopping search at 5*N yields sufficient reduction
    for p in range(2, 5*N):
        target = numerator % p
        if target:
            continue

        pp.append(p)
    
    counts = {p: [0]*p for p in pp}
    nonzeros = {}

    for n in range(2, 1 + N):
        z = denominator / n / n

        for p in pp:
            counts[p][z % p] += 1
            if z % p:
                nonzeros.setdefault(p, set())
                nonzeros[p].add(n)

    elim = set()

    for p in pp:
        if not can_make_zero(counts[p]):
            elim |= nonzeros[p]

    return sorted(list(set([p for p in pp if p <= N]) - elim))

def compute_table(values):
    table = {}
    # DFS
    def _compute(current, items):
        if len(items) == 0:
            table.setdefault(current, 0)
            table[current] += 1
            return

        # dont use item
        _compute(current, items[1:])

        # do use item
        _compute(current + items[0], items[1:])

    _compute(0, values)

    return table

if __name__ == '__main__':
    N = 80
    denominator = get_denominator(N)
    numerator = denominator / 2
    quarter = denominator / 4 # we know 1/2 is included

    valid_squares = reduce_candidate_squares(numerator, denominator, N)

    print('eliminated squares: %s' % str(sorted(list(set(range(2, 1+N)) - set(valid_squares)))))
    print('candidate set size reduced from %d => %d' % (N - 1, len(valid_squares)))
    print('candidate squares: %s' % str(valid_squares))

    N_left = len(valid_squares) / 2

    left_squares = valid_squares[1:N_left]
    print('left: %s' % str(left_squares))

    right_squares = valid_squares[N_left:]
    print('right: %s' % str(right_squares))

    table = compute_table([denominator / n / n for n in left_squares])
    print('built table')

    right_table = compute_table([denominator / n / n for n in right_squares])

    result = 0

    for (value, ways) in right_table.iteritems():
        left_ways = table.get(numerator - value - quarter, 0)
        result += ways * left_ways

    print('solution: %d' % result)
