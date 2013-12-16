#include<cstdio>
#include<cstdlib>
#include<cstring>

#define GRIDN 1001
int main(void)
{
	int **grid;
	grid = (int **) malloc(GRIDN*sizeof(int *));
	int i, j;
	for(i = 0; i < GRIDN; i++) {
		grid[i] = (int *) malloc(GRIDN*sizeof(int));
		memset(grid[i], 0, GRIDN*sizeof(int));
	}

	int center = GRIDN/2;
	int l=0, m;
	int diagsum = 0;
	int k = 1;
	
	i = GRIDN/2;
	j = i;
	grid[i][j] = k++;

	while(k < GRIDN*GRIDN) {
		l++;
		j++;
		for(m = i; m <= center + l; m++)
			grid[m][j] = k++;

		i = center + l;

		for(m = j-1; m >= center - l; m--)
			grid[i][m] = k++;

		j = center - l;

		for(m = i-1; m >= center - l; m--)
			grid[m][j] = k++;

		i = center - l;

		for(m = j+1; m <= center + l; m++)
			grid[i][m] = k++;

		j = center + l;
	}

	for(i = 0; i < GRIDN; i++)
		diagsum += grid[i][i] + grid[GRIDN-i-1][i];

	printf("diagonal sum: %d\n", diagsum-1); // don't double-count 1.


	return 0;

}