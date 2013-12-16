#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int Ncomb(int n0, int ndenom, int depth)
{
	int retVal = 0;
	if(!ndenom) 
		return 0;

	for(int ndenom0 = 0; ndenom0*depth <= n0; ndenom0++)
		if(ndenom0*depth == n0)
			retVal += 1;
		else
			retVal += Ncomb(n0 - ndenom0*depth, ndenom - 1, depth + 1);

	return retVal;
}


int main(int argc, char **argv)
{
	int N;
	if(argc != 2) 
		printf("Error: must provide input argument\n");
	else {
		N = atoi(argv[1]);

		int denom[N-1];
        int i;
        for(i = 0; i < N-1; i++)
            denom[i] = i+1;

		cout << "Number of ways to make " << N << " : " << Ncomb(N, N-1, 1) << endl;
	}
	return 0;
}
