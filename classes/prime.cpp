#include "prime.h"
using namespace std;

prime::prime(int MaxN):Nmax(MaxN)
{
	iscomposite = new char[MaxN + 1];
	memset(iscomposite, 0, (MaxN + 1)*sizeof(char));
	int *tmp = new int[MaxN + 1];
	nprimes = 0;
	for(int k = 2; k <= MaxN; k++) {
		if(!iscomposite[k]) {
			tmp[nprimes++] = k;
			for(int l = 2*k; l <= MaxN; l += k)
				iscomposite[l] = 1;
		}
	}
	prime_list = new int[nprimes];
	memcpy(prime_list, tmp, nprimes*sizeof(int));
	delete [] tmp;
}

std::vector<int> prime::primes()
{
	std::vector<int> ret(nprimes, 0);
	for(int i = 0; i < nprimes; i++)
		ret[i] = prime_list[i];

	return ret;
}

std::vector<int> prime::factor(int n)
{
	std::vector<int> ret(nprimes, 0);
	ret.reserve(nprimes);
	int k = 0;
	int n0 = n;

	while(n > 1 && k < nprimes) {
		while(!(n % prime_list[k])) {
			n /= prime_list[k];
			ret[k]++;
		}
		k++; 
	}
	if(n > 1)
		std::cout << "Error: prime factorization of " << n0 << " incomplete.\n";

	return ret;
}

int prime::fac2int(std::vector<int> x)
{
	if(x.size() > nprimes) {
		std::cout << "Error: invalid factored vector.\n";
		return -1;
	}
	
	int ret = 1;
	for(int i = 0; i < x.size(); i++)
		for(int j = 0; j < x[i]; j++)
			ret *= prime_list[i];

	return ret;
}

bool prime::isprime(int n) 
{
	bool ret;
	if(n < Nmax)
		ret = !iscomposite[n];
	else {
		int k = 0;
		while((n % prime_list[k]) && (n > prime_list[k]*prime_list[k]) && (k+1 < nprimes))
			k++;

		ret = n % prime_list[k];

		if(ret && (((long long) Nmax)*((long long) Nmax) < n)) {
			std::cout << "isprime() warning: number is too big to be certain!\n";
		}
	}
	return ret;
}

bool prime::llisprime(long long n) 
{
	bool ret;
	if(n < Nmax)
		ret = !iscomposite[n];
	else {
		int k = 0;
		while((n % prime_list[k]) && (n > ((long long) prime_list[k])*((long long) prime_list[k])) && (k+1 < nprimes))
			k++;

		ret = n % prime_list[k];

		if(ret && (((long long) Nmax)*((long long) Nmax) < n))
			std::cout << "isprime() warning: number is too big to be certain!\n";
	}
	return ret;
}

prime::~prime()
{
	if(iscomposite)
		delete [] iscomposite;
	if(prime_list)
		delete [] prime_list;
}	

