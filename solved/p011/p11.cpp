#include<cstdio>
#include<cstdlib>

int left(int [20][20], int, int);
int right(int [20][20], int, int);
int up(int [20][20], int, int);
int down(int [20][20], int, int);
int lu(int [20][20], int, int);
int ld(int [20][20], int, int);
int ru(int [20][20], int, int);
int rd(int [20][20], int, int);

int main(void)
{
	FILE *data = fopen("data11.txt", "r");
	if(!data) {
		printf("Error opening file.\n");
		exit(1);
	}
	char readbuf[3];
	int grid[20][20];
	int i = 0, j = 0, maxProd, x;
	while(!feof(data)) {
		fread(readbuf, sizeof(char), 3, data);
		if(readbuf[0] == '\n') {
			readbuf[0] = readbuf[1];
			readbuf[1] = readbuf[2];
			readbuf[2] = '\0';
			j = 0;
			grid[++i][j] = atoi(readbuf);
		} else {
			readbuf[2] = '\0';
			grid[i][j++] = atoi(readbuf);
		}
	}
	fclose(data);
	maxProd = 0;
	printf("Input grid: \n");
	for(i = 0; i < 20; i++) {
		for(j = 0; j < 20; j++) {
			printf("%d ", grid[i][j]);
			x = up(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = down(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = left(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = right(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = lu(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = ld(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = ru(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
			x = rd(grid, i, j);
			maxProd = (x>maxProd)?x:maxProd;
		}
		printf("\n");
	}
	printf("Maximum linear product: %d\n", maxProd);
}

int left(int grid[20][20], int i, int j)
{
	return (j<3)?0:grid[i][j]*grid[i][j-1]*grid[i][j-2]*grid[i][j-3];
}

int right(int grid[20][20], int i, int j)
{
	return (j>16)?0:grid[i][j]*grid[i][j+1]*grid[i][j+2]*grid[i][j+3];
}

int up(int grid[20][20], int i, int j)
{
	return (i<3)?0:grid[i][j]*grid[i-1][j]*grid[i-2][j]*grid[i-3][j];
}

int down(int grid[20][20], int i, int j)
{
	return (i>16)?0:grid[i][j]*grid[i+1][j]*grid[i+2][j]*grid[i+3][j];
}

int lu(int grid[20][20], int i, int j)
{
	return (i<3 || j<3)?0:grid[i][j]*grid[i-1][j-1]*grid[i-2][j-2]*grid[i-3][j-3];
}

int ld(int grid[20][20], int i, int j)
{
	return (i>16 || j<3)?0:grid[i][j]*grid[i+1][j-1]*grid[i+2][j-2]*grid[i+3][j-3];
}

int ru(int grid[20][20], int i, int j)
{
	return (i<3 || j > 16)?0:grid[i][j]*grid[i-1][j+1]*grid[i-2][j+2]*grid[i-3][j+3];
}

int rd(int grid[20][20], int i, int j)
{
	return (i>16 || j > 16)?0:grid[i][j]*grid[i+1][j+1]*grid[i+2][j+2]*grid[i+3][j+3];
}
