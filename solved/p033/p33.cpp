#include<cstdio>

void digits(int, int[]);

int main(void)
{
	int ndigits[2], ddigits[2];
	int counted[100];

	int i, j, k, kmin, kmax, N, M;
	int count=0;

	for(i=1; i < 10; i++)
		for(j=i+1; j < 10; j++) {
			if(j % i || i == 1) {
				kmin = 10/i + 10%i + 1;
				kmax = 100/j+1;
				for(k = kmin; k < kmax ; k++) {
					M = i*k;
					N = j*k;
					digits(M, ndigits);
					digits(N, ddigits);
					if(ddigits[0] == ndigits[0] && ddigits[1]*i == ndigits[1]*j && ddigits[0] != 0) {
						printf("One such pair: %d/%d\n", M, N);
						count++;
					}
					if(ddigits[0] == ndigits[1] && ddigits[1]*i == ndigits[0]*j && ddigits[0] != 0) {
						printf("One such pair: %d/%d\n", M, N);
						count++;
					}
					if(ddigits[1] == ndigits[0] && ddigits[0]*i == ndigits[1]*j && ddigits[1] != 0) {
						printf("One such pair: %d/%d\n", M, N);
						count++;
					}
					if(ddigits[1] == ndigits[1] && ddigits[0]*i == ndigits[0]*j && ddigits[1] != 0) {
						printf("One such pair: %d/%d\n", M, N);
						count++;
					}
				}
			} 
		}

	printf("Counted %d numbers.\n", count);
	return 0;
}
	
void digits(int N, int dig[])
{
	dig[0] = N / 10;
	dig[1] = N % 10;
	return;
}
