#include<iostream>
#include<vector>
#include "prime.h"
using namespace std;

int main(void)
{
	prime P(1000);

	cout << "First 10 primes:\n";
	for(int k = 0; k < 10; k++)
		cout << P.p(k) << " ";

	vector <int> f = P.factor(114);
	cout << "Factorization of 114:\n";
	for(int k = 0; k < 10; k++)
		cout << P.p(k) << "^" << f[k] << ", ";
	
	cout << endl;

	cout << "Testing isprime():\n";
	cout << "\tisprime(9007) == " << P.isprime(9007) << endl;
	cout << "\tisprime(9008) == " << P.isprime(9008) << endl;
	cout << "\tisprime(9009) == " << P.isprime(9008) << endl;

	return 0;
}
