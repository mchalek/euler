#include<cstdio>
#include<cstdlib>

#define NROWS 100 // for problem 67
//#define NROWS 15 // for problem 18
#define NUMLEN 2

int main(void)
{
	FILE *fin = fopen("data67.txt", "r");
	//FILE *fin = fopen("data18.txt", "r");
	int grid[NROWS][NROWS];

	int i, j;
	char buf[NUMLEN+1];

	for(i = 0; i < NROWS; i++)
		for(j = 0; j <= i; j++) {
			fread(buf, sizeof(char), NUMLEN+1, fin);
			buf[NUMLEN] = '\0';
			grid[i][j] = atoi(buf);
		}
	fclose(fin);

	i = NROWS - 2;
	while(i >= 0) {
		for(j = 0; j <= i; j++)
			grid[i][j] += grid[i+1][j] > grid[i+1][j+1] ? grid[i+1][j] : grid[i+1][j+1];
		i--;
	}

	printf("Maximum sum: %d\n", grid[0][0]);
	return 0;
}
