#include<cstdio>
#include<cstdlib>
// prime factorize each number, then compute the number of factors by taking all
// combinations of primes.
int count_divisors(long long, int *primes, int);
#define MAX_CHECK 1000

int main(void)
{
	long long tnum = 1, topsum = 1;

	int nprimes = 0;
	int i, j;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *prime_list = (int *) calloc(MAX_CHECK+1, sizeof(int));

	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			prime_list[nprimes++] = i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	while(count_divisors(tnum, prime_list, nprimes) <= 500) {
		tnum += ++topsum;
	}

	printf("With %d divisors, %d is the first triangle number with > 500 divisors.\n", count_divisors(tnum, prime_list, nprimes), tnum);
	return 0;
}

int count_divisors(long long n, int *prime_list, int nprimes)
{
	int ret, i, j;

	ret = 1;
	i = 0;
	while(n > 1 && i < nprimes) {
		j = 0;
		while(!(n % prime_list[i])) {
			j++;
			n /= prime_list[i];
		}
		ret *= j+1;
		i++;
	}

	if(i == nprimes)
		ret = 0; // error, prime_list doesn't go high enough.  perhaps n is prime and big?

	return ret;
}