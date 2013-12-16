#include<iostream>
#include<cmath>
using namespace std;

bool ispan(long long);
long long concat(long long, long long);

int main(void)
{
	long long N, Nmax = 1;
	int n, nmax, k;
	
	for(n = 2; n < 9999; n++) {
		k = 1;
		N = n*k;
		while(N < 999999999LL && !ispan(N))
			N = concat(N, (++k)*n);

		if(N < 999999999LL && ispan(N) && N > Nmax) {
			Nmax = N;
			nmax = n;
		}
	}

	cout << "Largest concatenated pandigital product: " << Nmax << endl;

}

long long concat(long long N, long long k)
{
	N = (long long) N * pow(10, ceil(log10((double) k)));
	N *= (log10((double) k) == ceil(log10((double)k))) ? 10 : 1;
	return N + k;
}

bool ispan(long long N)
{
	bool digits[10];
	bool ok = true;
	int i;
	for(i = 0; i < 10; i++)
		digits[i] = false;

	do {
		digits[N % 10] = true;
		N /= 10;
	} while(N);
	
	for(i = 1; i < 10; i++)
		ok = digits[i] ? ok : false;

	return ok;
}
