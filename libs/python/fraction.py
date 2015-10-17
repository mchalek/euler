#!/usr/bin/python
from primes import Factorer

factorer = Factorer()

class Fraction:
    def __init__(self, num, den, negative=False):
        if type(num) == dict and type(den) == dict:
            self.negative = negative
            self.fn = num
            self.fd = den
        else:
            if num * den < 0:
                self.negative = not negative
            else:
                self.negative = negative

            if num < 0:
                num = -num

            if den < 0:
                den = -den

            self.fn = factorer.factor(num)
            self.fd = factorer.factor(den)

    def reduce(self):
        k0 = set(self.fn.keys())
        k1 = set(self.fd.keys())

        common = k0 & k1

        for p in common:
            if p == 1: # don't discard the 1, needed to distinguish 1 from 0
                continue

            nn = self.fn.pop(p)
            nd = self.fd.pop(p)

            if nn > nd:
                self.fn[p] = nn - nd
            elif nn < nd:
                self.fd[p] = nd - nn

    def prod(self, factors):
        if len(factors) == 0:
            return 0
        else:
            return reduce(lambda x, y: x * y, [p**e for (p, e) in factors.items()])

    def __str__(self):
        return '%d/%d' % self.tuple()

    def __repr__(self):
        return self.__str__()

    def factored_multiply(self, a, b):
        product = {p:e for (p, e) in a.items()}
        for (p, e) in b.items():
            prev = product.get(p, 0)
            product[p] = e + prev

        return product

    def tuple(self):
        self.reduce()
        if self.negative:
            numerator = -self.prod(self.fn)
        else:
            numerator = self.prod(self.fn)

        denominator = self.prod(self.fd) if numerator != 0 else 0

        return (numerator, denominator)

    def clone(self):
        return Fraction(self.fn, self.fd, self.negative)

    def __add__(self, that):
        if type(that) == int:
            return self.__add__(Fraction(that, 1))

        if self == 0:
            return that.clone()

        if that == 0:
            return self.clone()
        
        new_fd = self.factored_multiply(self.fd, that.fd)

        A = self.prod(self.factored_multiply(self.fn, that.fd))
        if self.negative:
            A = -A

        B = self.prod(self.factored_multiply(that.fn, self.fd))
        if that.negative:
            B = -B

        new_num = A + B
        new_neg = new_num < 0
        if new_neg:
            new_num = -new_num

        new_fn = factorer.factor(new_num)

        return Fraction(new_fn, new_fd, new_neg)

    def __mul__(self, that):
        if type(that) == int:
            return self.__mul__(Fraction(that, 1))

        if len(self.fn) == 0 or len(that.fn) == 0:
            return Fraction(0,1)

        new_fn = {p:e for (p, e) in self.fn.items()}
        for (p, e) in that.fn.items():
            prev = new_fn.get(p, 0)
            new_fn[p] = e + prev

        new_fd = {p:e for (p, e) in self.fd.items()}
        for (p, e) in that.fd.items():
            prev = new_fd.get(p, 0)
            new_fd[p] = e + prev

        new_negative = self.negative ^ that.negative

        return Fraction(new_fn, new_fd, new_negative)

    def __rmul__(self, that):
        return self.__mul__(that)

    def __radd__(self, that):
        return self + that

    def __sub__(self, that):
        return self + (that * -1)

    def __rsub__(self, that):
        return (self * -1) + that

    def inverse(self):
        return Fraction(self.fd, self.fn)

    def div(self, that):
        if type(that) == int:
            return self * Fraction(1, that)

        return self * that.inverse()

    def __lt__(self, that):
        if type(that) == int:
            return self < Fraction(that, 1)

        (n0,d0) = self.tuple()
        (n1,d1) = that.tuple() 

        return n0*d1 < d0*n1

    def __eq__(self, that):
        if type(that) == int:
            return self == Fraction(that, 1)

        return self.tuple() == that.tuple()

    def __gt__(self, that):
        if type(that) == int:
            return Fraction(that, 1) < self

        return that < self

if __name__ == '__main__':
    f0 = Fraction(10, 30)
    f1 = Fraction(8, 10)

    print(f0)
    print(f1)
    print('%s - 1: %s' % (str(f0), str(f0-1)))
    print('1 - %s: %s' % (str(f0), str(1-f0)))
    f2 = f0 * f1
    print('%s * %s == %s' % (str(f0), str(f1), str(f2)))
    f3 = f0 + f1
    print('%s + %s == %s' % (str(f0), str(f1), str(f3)))
    f4 = f1 - f0 + Fraction(3,16)
    print('%s - %s == %s' % (str(f1), str(f0), str(f4)))

    print('sum of all of them: %s' % str(sum([f0,f1,f2,f3,f4])))

