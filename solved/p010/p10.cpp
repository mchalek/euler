#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 2000000

int main(void)
{
	unsigned long long prime_sum = 0;
	int i, j;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			prime_sum += i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

		printf("sum of primes below 2e6: %lld\n", prime_sum), 

	free(iscomposite);
	return 0;
}