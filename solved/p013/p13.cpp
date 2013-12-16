#include<cstdio>
#include<cstdlib>

#define NNUM 100
#define NDIG 50
int main(void)
{
	FILE *data = fopen("data13.txt", "r");
	if(!data) {
		printf("Error opening file.\n");
		exit(1);
	}
	char readbuf[51], tmp[2];
	int digits[100][50];
	int sumdigits[53], colsum, ndig;
	
	int i = 0, j = 0;
	tmp[1] = '\0';
	while(!feof(data)) {
		fread(readbuf, sizeof(char), NDIG+1, data);
		for(j = 0; j < NDIG; j++) {
			tmp[0] = readbuf[j];
			digits[i][NDIG-j-1] = atoi(tmp);
		}
		++i;
	}
	fclose(data);
	
	for(i = 0; i < 53; i++)
		sumdigits[i] = 0;

	colsum = 0;
	for(i = 0; i < NDIG; i++) {
		for(j = 0; j < NNUM; j++)
			colsum += digits[j][i];

		sumdigits[i] = colsum % 10;
		colsum /= 10;
	}
	ndig = NDIG;
	while(colsum > 0) {
		sumdigits[ndig++] = colsum % 10;
		colsum /= 10;
	}

	printf("I finished the sum (has %d digits). The first ten digits are:\n", ndig+1);
	for(i = ndig-1; i > ndig-11; i--) {
		printf("%d ", sumdigits[i]);
	}
	printf("\n");

	return 0;
}

