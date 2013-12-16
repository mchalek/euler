#include<cstdio>
#include<cstdlib>

void fill(int *, int, int, int);

int main(void)
{
	int i, j, n;
	int *P4 = (int *) calloc(28, sizeof(int));
	int *P6 = (int *) calloc(31, sizeof(int));
	
	double *P4d = (double *) calloc(28, sizeof(double));
	double *P6d = (double *) calloc(31, sizeof(double));

	fill(P4, 4, 9, 0);
	fill(P6, 6, 6, 0);

	n = 0;
	for(i = 0; i < 28; i++)
		n+= P4[i];

	for(i = 0; i < 28; i++)
		P4d[i] = ((double) P4[i]) / ((double) n);

	n = 0;
	for(i = 0; i < 31; i++)
		n+= P6[i];

	for(i = 0; i < 28; i++)
		P6d[i] = ((double) P6[i]) / ((double) n);

	double Ans = 0;
	for(i = 0; i < 28; i++)
		for(j = 0; j < i+3; j++)
			Ans += P4d[i]*P6d[j];

	printf("Win probability: %.8g\n", Ans);
	return 0;
}

void fill(int *P, int nsides, int ndie, int total)
{
	if(ndie == 0) {
		P[total]++;
		return;
	}	

	for(int i = 0; i < nsides; i++)
		fill(P, nsides, ndie-1, total+i);

	return;
}
