#include<cstdio>
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

		int denom[] = {1, 2, 5, 10, 20, 50, 100, 200};

		cout << "Number of ways to make " << N << " pence: " << Ncomb(N, 8, denom) << endl;
	}
	return 0;
}
