#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 1000000

int main(void)
{
	int i, j, p, nprimes=0, maxN, maxA, Ans;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *primes = (int *) calloc(MAX_CHECK+1, sizeof(int));
	
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			primes[nprimes++] = i;	
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}
	Ans = 0;
	i = 1;
	p = 1 + 3*i*(i+1);
	while(p <= MAX_CHECK) {
		if(!iscomposite[p]) {
			Ans++;
			printf("%d^3 + %d^2*%d == %d^3\n", i*i*i, i*i*i, p, i*i*(i+1));
		}
		i++;
		p = 1 + 3*i*(i+1);
	}
	
	printf("Discovered %d of these primes.\n", Ans);
	free(iscomposite);
	free(primes);
	return 0;
}

