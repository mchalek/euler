#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 1000000
int main(void)
{
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

	printf("number of primes less than %d: %d\n", MAX_CHECK, nprimes);
	printf("first ten primes: ");
	for(i = 0; i < 10; i ++)
		printf("%i   ", prime_list[i]);
	printf("\n10001th prime: %i\n", prime_list[10000]);
	free(iscomposite);
	free(prime_list);
	return 0;
}