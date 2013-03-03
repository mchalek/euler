#include<iostream>
#include<cstdlib>
#include<prime.h>
using namespace std;

double computeR(int m, int factors[], long long & N)
{
	long long num = m*(m-3)/2;
	int *tmp = new int[m];
	
	N = 4096*243;
	for(int k = 0; k < m; k++) {
		N *= factors[k]; /*
		if(factors[k] == 1) {
			memcpy(tmp, factors + k + 1, (m-k-1)*sizeof(int));
			memcpy(factors + k, tmp, (m-k-1)*sizeof(int));
			m--;
			cout << "Removing a factor of 1\n";
		}*/
	}
	for(int k = 0; k < m; k++) {
		num += N / factors[k];
		for(int l = 0; l < k; l++) 
			num -= N / (factors[k]*factors[l]);
	}
	delete [] tmp;
	return ((double) N - 1 - num) / (N-1);
}

int main(int argc, char **argv)
{
	long long N;
	const int Nmax = 10;
	prime P(Nmax);

	int factors[4];	

	double R, Rmin = 1;
	int i = 0, j = 0, k = 0, l = 0;
	
	while(i++ < P.nprime()) {
		j = i;
		while(j++ < P.nprime()) {
			k = j;
			while(k++ < P.nprime()) {
				l = k;
				while(l++ < P.nprime()) {
					factors[0] = P.p(i-1);
					factors[1] = P.p(j-1);
					factors[2] = P.p(k-1);
					factors[3] = P.p(l-1);
					R = computeR(2, factors, N);
					if(R < Rmin) {
						Rmin = R;
						cout << "R(" << N << ") == " << R << endl;
					}
				}
			}
		}
	}

	return 0;
}
