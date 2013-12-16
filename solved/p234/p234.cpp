#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 1100000
#define UB 999966663333

int main(void)
{
	int i, j, nprimes=0;
	unsigned long long lb, ub, k, semisum=0;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	long long *primes = (long long *) malloc((MAX_CHECK+1)*sizeof(long long));
	
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			primes[nprimes++] = i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	i = 0;
	lb = primes[i]*primes[i];
	ub = primes[i+1]*primes[i+1];
	while(lb < UB) {
		for(k = primes[i]*(1+primes[i]); k < ub; k += primes[i])
			if(k % primes[i+1] && k <= UB)
				semisum += k;

		for(k = primes[i+1]*(primes[i+1]-1); k > lb; k -= primes[i+1])
			if(k % primes[i] && k <= UB)
				semisum += k;
		++i;
		lb = primes[i]*primes[i];
		ub = primes[i+1]*primes[i+1];
	}

	printf("sum of semidivisible numbers below %lld: %lld\n", UB, semisum);

	free(iscomposite);
	free(primes);
	return 0;
}