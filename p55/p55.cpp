#include<iostream>
#include<cmath>
using namespace std;

long long reverse(long long n);

int main(void)
{
	int k, c, n = 0;
	long long l, m;

	for(k = 5; k < 10000; k++) {	
		c = 0;
		l = k + reverse(k); // Do this once before loop to capture palindromic lycherel numbers
		m = reverse(l);
		while(c < 55 && m != l) {
			c++;
			l += m;
			m = reverse(l);
		}
		n += l != m;
	}

	cout << n << " lycherel numbers below 10000.\n";
	
	return 0;	
}

long long reverse(long long n)
{
	int Ndig = ceil(log10(n));
	long long ret = 0;
	Ndig = (log10(n) > Ndig) ? Ndig + 1 : Ndig;	
	
	long long p = 1, q = 1;
	for(int k = 1; k < Ndig; k++)
		p *= 10;
	
	for(int k = 0; k < Ndig; k++) {
		ret += q*(n / p);
		n %= p;
		q *= 10;
		p /= 10;
	}

	return ret;

}
