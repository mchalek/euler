#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 1000000


int main(void)
{
	int i, j, k, sum, nprimes=0, nAns, Ans;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *primes = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *biggestSum = (int *) calloc(MAX_CHECK+1, sizeof(int));
		
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			primes[nprimes++] = i;	
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	for(i = 0; i < nprimes-1; i++) { // Dont go up to nprimes, since it won't be a sum
		j = i + 1;
		sum = primes[i]+primes[j];
		while(sum < MAX_CHECK) {
			biggestSum[sum] = biggestSum[sum] < j-i+1 ? j-i+1 : biggestSum[sum];		
			
			j++;
			sum = primes[i];
			for(k = i+1; k <= j; k++)
				sum += primes[k];
		}	
	}

	nAns = 0;
	Ans = 0;

	for(i = 0; i <= nprimes; i++) {
		if(biggestSum[primes[i]] > nAns) {
			nAns = biggestSum[primes[i]];
			Ans = primes[i];
		}
	}

	printf("I get the prime %d, a sum of %d consecutive primes.\n", Ans, nAns);


	free(iscomposite);
	free(primes);
	return 0;
}

