#include<cstdio>
#include<cstdlib>

int main(void)
{
	int *counts = (int *) calloc(1001, sizeof(int));
	int *psquares = (int *) calloc(1000001, sizeof(int));
	int *roots = (int *) calloc(1000001, sizeof(int));
	int Nmax = 0, pmax = 0;

	int i, j, csq, p;

	i = 1; 
	while(i < 1001) {
		psquares[i*i] = 1;
		roots[i*i] = i;
		++i;
	}

	for(i = 1; i < 999; i++) 
		for(j = i+1; j < 1000-i; j++) {
			csq = i*i + j*j;
			if(csq < 1000001) {
				if(psquares[csq] && i + j + roots[csq] < 1001) {
					p = i + j + roots[csq];
					counts[p]++;
					//printf("Adding one for perimeter %d (%d, %d, %d)\n", p, i, j, roots[csq]);
					if(counts[p] > Nmax) {
					//	printf("New max at: %d\n", p);
						Nmax = counts[i+j+roots[csq]];
						pmax = p;
					}
				}
			}
		}

	printf("Most popular perimeter: %d, with %d occurrences.\n", pmax, Nmax);
	
	return 0;
}