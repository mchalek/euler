#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<timer.h>

int main(void)
{
	tic();
	int n, m, k, nMax, tmp;
	const int mMax = (int) floor((-1+sqrt(1+4e6))/2);
	int nL = 0;
	int *L = (int *) calloc(1e7, sizeof(int));

	for(m = 2; m <= mMax; m++) {
		tmp = (1e6-m*m)/m;
		nMax = tmp < (m-1) ? tmp : m-1;
		for(n=1; n <= nMax; n++) {
			L[nL++] = k*2*m*(m+n);	
		}
	}
	
	printf("number of lengths: %d\n", nL);
	printf("first 10:\n");
	for(m = 0; m < 10; m++)
		printf("\t%d\n", L[m]);

	free(L);
	printf("Execution time: %gs\n", toc());
	return 0;
}
