#include<cstdio>
#include<prime.h>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int Ncomb(int n0, int ndenom, int denom[])
{
	int retVal = 0;
	if(!ndenom) 
		return 0;

	for(int ndenom0 = 0; ndenom0*denom[0] <= n0; ndenom0++)
		if(ndenom0*denom[0] == n0)
			retVal += 1;
		else
			retVal += Ncomb(n0 - ndenom0*denom[0], ndenom - 1, denom + 1);

	return retVal;
}


int main(int argc, char **argv)
{
	int N;
	if(argc != 2) 
		printf("Error: must provide input argument\n");
	else {
		N = atoi(argv[1]);

        prime p(1000);
        vector <int> list = p.primes();
        int nprimes = list.size();

        int *denom = new int[nprimes];
        int i;
        for(i = 0; i < nprimes; i++)
            denom[i] = list[i];

		cout << "Number of ways to make " << N << " pence: " << Ncomb(N, nprimes, denom) << endl;
	}
	return 0;
}
