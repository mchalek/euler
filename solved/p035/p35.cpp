#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 10000000
#define MAX_CIRC_TEST 1000000

bool is_circular(int, int *);

int main(void)
{
	int i, j, nprimes=0, ncirc=0;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *primes = (int *) calloc(MAX_CHECK+1, sizeof(int));
		
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			primes[nprimes++] = i;	
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	i = 0;
	printf("circular primes: \t\n");
	while(primes[i] <= MAX_CIRC_TEST) {
		if(is_circular(primes[i++], iscomposite)) {
			ncirc++;
			printf("%d   ", primes[i-1]);
		}
	}
	printf("\ni counted %d circular primes below 1e6\n", ncirc);
	free(iscomposite);
	return 0;
}

bool is_circular(int n, int *iscomposite)
{
	int ndig = 1;
	int i, j, k, test;
	int *digits;
	bool ret = true; // unless proven otherwise

	j = 10;
	while(n > j) {
		ndig++;
		j *= 10;
	}

	digits = (int *) malloc(ndig*sizeof(int));
	
	j = 10;
	for(i = 0; i < ndig; i++) {
		digits[i] = (10*(n % j))/j;
		n -= digits[i]*j/10;
		j *= 10;
	}

	for(i = 0; i < ndig; i++) {
		j = 1;
		test = 0;
		for(k = i; k < ndig; k++) {
			test += j * digits[k];
			j *= 10;
		}
		for(k = 0; k < i; k++) {
			test += j * digits[k];
			j *= 10;
		}
		ret &= !iscomposite[test];
	}
	free(digits);
	return ret;
}	
