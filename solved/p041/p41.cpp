#include<cstdlib>
#include<cstdio>
#include<cstring>
#define MAX_CHECK 7654321

int factorial(int i);
void generate_perm(int **, int *, int);

int main(void)
{
	int i, j, k, ntest;
	const int nperm = factorial(7);
	int digits[] = {1,2,3,4,5,6,7};
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int **permutations = (int **) malloc(nperm*sizeof(int *));
	for(i = 0; i < nperm; i++)
		permutations[i] = (int *) calloc(7, sizeof(int));
	
	generate_perm(permutations, digits, 7);

	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	i = nperm-1;
	while(i > -1) {
		ntest = 0;
		k = 1;
		for(j = 0; j < 7; j++) {
			ntest += permutations[i][6-j]*k;
			k *= 10;
		}

		if(!iscomposite[ntest]) 
			break;
		i--;
	}

	printf("Biggest pandigital prime: %d\n", ntest);
	free(iscomposite);
	return 0;
}

void generate_perm(int **perm, int *digits, int ndigits) 
{ // this generates an ordered list.  I think it is slowed down by memory operations, 
	// so it could be improved by sending it an allocated workspace.
	// yeah, definitely.  should be implemented as using a matrix, rather than a 2-D vector,
	// in which case recursive calls can be directed to fill in the appropriate regions of the 
	// matrix.
	if(ndigits == 1) {
		perm[0][0] = *digits;
		return;
	}
	int i, j;
	const int fnm1 = factorial(ndigits-1);
	int **tmp = (int **) malloc(fnm1*sizeof(int));
	int *new_digits = (int *) malloc((ndigits-1)*sizeof(int));

	for(i = 0; i < fnm1; i++)
		tmp[i] = (int *) malloc((ndigits-1)*sizeof(int));

	for(i = 0; i < ndigits; i++) {
		memcpy(new_digits, digits, i*sizeof(int));
		memcpy(new_digits+i, digits+i+1, (ndigits-i-1)*sizeof(int));
		generate_perm(tmp, new_digits, ndigits-1);
		for(j = 0; j < fnm1; j++) {
			perm[j+i*fnm1][0] = digits[i];
			memcpy(&perm[j+i*fnm1][1], tmp[j], (ndigits-1)*sizeof(int));
		}
	}
	for(i = 0; i < fnm1; i++)
		free(tmp[i]);

	free(tmp);
	free(new_digits);
}

int factorial(int i) {
	if(i == 1)
		return 1;
	else
		return i * factorial(i-1);
}
