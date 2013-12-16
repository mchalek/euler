#include<cstdio>
#include<cstdlib>

#define MAX_CHECK 10000 // how high to go with primes?

int comparator(const void *, const void *);

int main(void)
{
	int n4dprimes=0;
	int i, j, k;
	bool found = false;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *prime_list = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int npperm[1061], n, nset;
	int digits[4], perm[24][4], p_ix;
	int perm_list[1061][24];
	int *already_counted = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *differences;
	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			if(i > 1000)
				prime_list[n4dprimes++] = i; // only store 4-digit primes.

			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

		p_ix = 0;
	for(j = 0; j < 4; j++)
		for(k = 0; k < 4; k++)
			for(int l = 0; l < 4; l++)
				for(int m = 0; m < 4; m++)
					if(j != k && j != l && j != m && k != l && k != m && l != m) {
						perm[p_ix][0] = j;
						perm[p_ix][1] = k;
						perm[p_ix][2] = l;
						perm[p_ix++][3] = m;
					}

	nset = 0; // number of permutation sets
	for(i = 0; i < n4dprimes; i++) {
		n = 0;
		if(!already_counted[prime_list[i]]) {
			digits[0] = prime_list[i] % 10;
			digits[1] = (prime_list[i] / 10) % 10;
			digits[2] = (prime_list[i] / 100) % 10;
			digits[3] = (prime_list[i] / 1000) % 10;	

			for(j = 0; j < 24; j++) {
				k = 1000*digits[perm[j][0]] + 100*digits[perm[j][1]] + 10*digits[perm[j][2]] + digits[perm[j][3]];
				already_counted[k] = 1;
				if(!iscomposite[k] && k > 999)
					perm_list[nset][n++] = k;
			}
			if(n > 1)
				npperm[nset++] = n;
		}
	}
	
	// now sort the permutation sets and remove repeats from within sets.

	for(i = 0; i < nset; i++) {
		qsort(perm_list[i], npperm[i], sizeof(int), comparator);
		
		k = 1;
		j = 1;
		while(j < npperm[i] && k < npperm[i]) {
			while(perm_list[i][k] == perm_list[i][j-1] && k < npperm[i])
				k++;
			if(k < npperm[i])
				perm_list[i][j] = perm_list[i][k];
			j++; k++;
		}
		npperm[i] -= k-j;

		for(j = 0; j < npperm[i]; j++)
			for(k = j+1; k < npperm[i]; k++)
				for(int l = k + 1; l < npperm[i]; l++)
					if(perm_list[i][j] && perm_list[i][l] - perm_list[i][k] == perm_list[i][k] - perm_list[i][j]) {
						printf("Arithmetic sequence found in: \n");
						printf("%d, %d, %d\n", perm_list[i][j], perm_list[i][k], perm_list[i][l]);
					}
	}
	return 0;
}

int comparator(const void *a, const void *b)
{
	int x = *((int *) a);
	int y = *((int *) b);

	if(x<y)
		return -1;
	else 
		if(x == y)
			return 0;
		else
			return 1;
}