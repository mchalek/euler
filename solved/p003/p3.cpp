#include<cmath>
#include<cstdlib>
#include<cstdio>

#define MAX_CHECK 100000
#define NUMBER 600851475143
int main(void)
{
	int nprimes = 0;
	int i, j;
	unsigned long long remainder;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *prime_list = (int *) calloc(MAX_CHECK+1, sizeof(int));

	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			prime_list[nprimes++] = i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	i = 0; 
	remainder = NUMBER;
	while(remainder > prime_list[i] && i <= MAX_CHECK) {
		if(!(remainder % prime_list[i]))
			remainder /= prime_list[i];
		else
			i++;
	}

	if(remainder == prime_list[i])
		printf("Largest prime factor of input number: %d\n", prime_list[i]);
	else
		printf("Did not find solution.\n");

	free(iscomposite);
	free(prime_list);
	return 0;
}