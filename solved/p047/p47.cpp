#include<cstdio>
#include<cstdlib>

int count_distinct_primes(long long, int *primes, int);
#define MAX_CHECK 1000 // how high to go with primes?
#define NUM_DISTINCT 4 // how many distinct primes do you want?  for testing.

int main(void)
{
	int nprimes = 0;
	int i, j, k, k2;
	bool found = false;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *prime_list = (int *) calloc(MAX_CHECK+1, sizeof(int));

	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			prime_list[nprimes++] = i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}
	
	k = 10;
	while(!found) {
		k2 = k;
		while(count_distinct_primes(k2, prime_list, nprimes) == NUM_DISTINCT)
			k2++;
		if(k2 - k == NUM_DISTINCT)
			found = true;
		else
			k = k2+1;
	}
	
	printf("sequence of numbers found: ");
	for(i = k; i < k2; i++)
		printf("%d, ", i);

	return 0;
}

int count_distinct_primes(long long n, int *prime_list, int nprimes)
{
	int ret, i, j;

	ret = 0;
	i = 0;
	while(n > 1 && i < nprimes) {
		j = 0;
		while(!(n % prime_list[i])) {
			j = 1;
			n /= prime_list[i];
		}
		ret += j;
		i++;
	}

	if(i == nprimes)
		ret = 0; // error, prime_list doesn't go high enough.  perhaps n is prime and big?

	return ret;
}