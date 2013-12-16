#include <iostream>

int main(void)
{
	double *values[18];
	values[0] = new double[1];
	values[0][0] = 60;
	int Nmax = 1;
	int N[18];
	N[0] = 1;

	for(int k = 1; k < 18; k++) {
		values[k] = new double[Nmax *= 2];
		for(int j = 0; j < N[k-1]; j++) {
			values[k][2*j] = values[k-1][j] + values[0][0];
			values[k][2*j+1] = values[k-1][j]*values[0][0]/(values[k-1][j] + values[0][0]);
		}
	}
}