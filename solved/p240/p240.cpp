#include<iostream>
#include<cstring>
using namespace std;

//#define _TESTING

#ifndef _TESTING
#define SUM 70
#define NTOP 10
#define NDIE 20
#define NSIDES 12

#else

#define SUM 15
#define NTOP 3
#define NDIE 5
#define NSIDES 6

#endif

long long nchoosek(int n, int k)
{
	long long ret = 1;
	int lower = (k > n - k) ? n - k : k;
	int upper = (k > n - k) ? k : n - k;
	for(int i = n; i > upper; i--)
		ret *= i;

	for(int i = 2; i <= lower; i++)
		ret /= i;

	return ret;
}


int top_die(int Total, int Ndie, int minSide, int Nsides, int *out, int Nout) // returns # of configs
{
	int min_die0 = (Total > (Ndie-1)*Nsides) ? Total - (Ndie-1)*Nsides : 1;
	min_die0 = min_die0 < minSide ? minSide : min_die0;
	const int max_die0 = (Total > Nsides) ? Nsides : Total;

	int Nsubvalues, ret = 0;
	
	if(min_die0 > max_die0)
		return 0;

	if(Ndie == 1) { // if so there can only be one possible value.
		if(out)
			*out = max_die0;
		return 1;
	} else {
		for(int die0 = min_die0; die0 <= max_die0; die0++) {
			if(out) {
				Nsubvalues = top_die(Total - die0, Ndie-1, die0, Nsides, out + Nout + ret, Nout);
				for(int j = 0; j < Nsubvalues; j++)
					out[ret+j] = die0;
				ret += Nsubvalues;
			} else
				ret += top_die(Total - die0, Ndie-1, die0, Nsides, NULL, Nout);
		}
	}

	return ret;
}

void cfg2N(int ncfg, int *cfgs, int Ndie, int *N, int Nsides)
{
	memset(N, 0, Nsides*ncfg*sizeof(int));
	for(int i = 0; i < ncfg; i++)
		for(int j = 0; j < Ndie; j++)
			N[i + (cfgs[i + j*ncfg]-1)*ncfg]++; 
	return;
}

int main(void)
{
	const int nvalid = top_die(SUM, NTOP, 1, NSIDES, NULL, 0);
	int *cfgs = new int[nvalid*12];
	int *N = new int[nvalid*NSIDES];
	long long nways = 0, ntmp;
	int lowest, nremain;

	top_die(SUM, NTOP, 1, NSIDES, cfgs, nvalid);
	cfg2N(nvalid, cfgs, NTOP, N, NSIDES);
/*
	for(int i = 0; i < 3; i++) {
		for(int n = 0; n < NSIDES; n++)
			cout << N[i+n*nvalid] << ", ";
		cout << endl;
	}
	
	for(int n = 0; n < nvalid; n++) {
		cout << "(";
		for(int m = 0; m < NTOP; m++)
			cout << cfgs[n+m*nvalid] << ", ";
		cout << ")\n";
	}
*/
	cout << nvalid << " distinct configurations.\n";

	for(int i = 0; i < nvalid; i++) {
		lowest = cfgs[i] - 1;
		if(!lowest) {
				// first the number of ways to choose the lowest of the top 10
				ntmp = nchoosek(NDIE, N[i + lowest*nvalid] + NDIE - NTOP);
				// next the number of ways to choose the die below the lowest
				
				nremain = NTOP-N[i + lowest*nvalid];
				for(int j = 1; j < NSIDES; j++) {
					ntmp *= nchoosek(nremain, N[i + j*nvalid]);
					nremain -= N[i + j*nvalid];
				}

				nways += ntmp;
		} else 
			for(int nlowest = 0; nlowest <= NDIE - NTOP; nlowest++) {
				// first the number of ways to choose the lowest of the top 10
				ntmp = nchoosek(NDIE, N[i + lowest*nvalid]+nlowest);
				// next the number of ways to choose the die below the lowest
				for(int j = 0; j < NDIE-NTOP-nlowest; j++)
					ntmp *= lowest;
				nremain = NDIE-N[i + lowest*nvalid] - nlowest;

				for(int j = lowest+1; j < NSIDES; j++) {
					ntmp *= nchoosek(nremain, N[i + j*nvalid]);
					nremain -= N[i + j*nvalid];
				}

				nways += ntmp;
			}
	}

	cout << "I count " << nways << " ways.\n";
	delete [] cfgs;
}
