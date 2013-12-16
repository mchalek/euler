#include<cstdio>
#include<cstdlib>
#include<cstring>

#define N 9
#define n0 1000000
int factorial(int);
void generate_perm(int **perm, int *digits, int ndigits);

int comparator(const void *, const void *);

int main(void)
{
	int remaining = n0;
	int k = N;
	while(remaining != 0) {
		printf("complete cycles: %d\n", remaining / factorial(k));
		remaining = remaining % factorial(k--);
	} // should be able to get answer like this (no code needed, really) but
	// i screwed something up with remainders.  I end up getting 2783915604, but answer is
	// 2783915460, which comes right before my pen-and-paper answer. whatev, my recursive 
	// permutation generator was fun to write, sort of...
	
	int i, fN = factorial(N);
	int **perm = (int **)malloc(fN*sizeof(int *)); // 9!
	int *digits = (int *) malloc(N*sizeof(int));
	
	for(i = 0; i < fN; i++)
		perm[i] = (int *) malloc((N+1)*sizeof(int));

	digits[0] = 0; // We know the desired number starts with 1.
	digits[1] = 1;
	for(i = 2; i < N; i++)
		digits[i] = i+1;

	generate_perm(perm, digits, N);

	printf("the answer by direct computation is: 2");
	for(int j = 0; j < N; j++)
		printf("%d", perm[274240-1][j]);
	printf("\n");
		
	return 0;
}

void generate_perm(int **perm, int *digits, int ndigits) 
{ // this generates an ordered list.  I think it is slowed down by memory operations, 
	// so it could be improved by sending it an allocated workspace.
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
