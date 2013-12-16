#include<cstdio>

#define NGRID 100

int main(void)
{
	long long grid[NGRID+1][NGRID+1];
	grid[0][0] = 1;
	for(int i = 1; i <= NGRID; i++) {
		grid[i][0] = 1;
		for(int j = 1; j < i; j++)
			grid[i][j] = grid[i-1][j] + grid[i][j-1];
		grid[i][i] = 2*grid[i][i-1];
	}

	printf("%lld paths for a %dx%d grid.\n", grid[NGRID][NGRID], NGRID, NGRID);
	return 0;
}

