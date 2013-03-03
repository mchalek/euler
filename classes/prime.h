#include<cstring>
#include<iostream>
#include<vector>
class prime {
	private: 
		char *iscomposite; // use char because I understand it.
				   // I would use bool if I knew that I could
				   // use memset(), which I am skeptical about
				   // if sizeof(bool) = 1 bit (which I don't
				   // actually think it is...)
		int *prime_list;
		int nprimes;
		int Nmax;

	public:
		prime(int);

		bool isprime(int n);
		bool llisprime(long long n);
		
		// Note the functions below are trusted, n is not checked
		inline int p(int n) const { return prime_list[n]; };
		inline int nprime() const { return nprimes; };
		std::vector<int> primes();
	
		std::vector<int> factor(int);
		int fac2int(std::vector<int>);
		
		~prime();
};

