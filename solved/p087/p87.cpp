#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 7072 // 7072^2 > 5e7
#define ULIM 50000000


int main(void)
{
	int i, j, k, nprimes=0, Ans;
	long long t3, t4, sum;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *primes = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *sums = (int *) calloc(ULIM, sizeof(int)); // liberal use of main memory
		
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			primes[nprimes++] = i;	
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

		for(i = 0; i < nprimes; i++) {
			t4 = primes[i]*primes[i]*primes[i]*primes[i];
			if(t4 <= ULIM) {
				for(j = 0; j < nprimes; j++) {
					t3 = primes[j]*primes[j]*primes[j];
					if(t4+t3 <= ULIM) {
						for(k = 0; k < nprimes; k++) {
							sum = t4+t3+primes[k]*primes[k];
							if(sum <= ULIM)
								sums[sum] = 1;
							else
								break;
						}
					} else 
						break;
				}
			} else
				break;
		}

	Ans = 0;
	for(i = 0; i < ULIM; i++)
		Ans += sums[i];
		
	printf("I counted %d numbers.\n", Ans);
	free(iscomposite);
	free(primes);
	return 0;
}

