class BitArray:
    def __init__(self, N):
        self.N = N
        self.word_size = 64

        word_size = self.word_size
        
        num_words = (N + word_size) / word_size
        self.words = [0l]*num_words

    def index(self, k):
        if k >= self.N:
            raise Exception('Cannot retrieve index %d of a BitArray of size %d!' % (k, self.N))
        word_idx = k / self.word_size
        bit_idx = k % self.word_size

        return (word_idx, bit_idx)

    def get(self, k):
        (word_idx, bit_idx) = self.index(k)

        if 1 == ((self.words[word_idx] >> bit_idx) & 1):
            return True
        else:
            return False

    def set(self, k):
        (word_idx, bit_idx) = self.index(k)

        self.words[word_idx] |= (1 << bit_idx)

def primes(N):
    is_comp = BitArray(N)
    result = [2]

    for p in range(3, N, 2):
        if is_comp.get(p):
            continue

        result.append(p)

        q = p + p
        while q < N:
            is_comp.set(q)

            q += p

    return result
