#include "prime.h"
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

long long S(int n, prime &P);
void fillbool(long long start, int stop, vector<bool> &v, prime &P);

int main(void)
{
	prime P(5100000);
	cout << "S(8) == " << S(8, P) << endl;
	cout << "S(9) == " << S(9, P) << endl;
	cout << "S(10000) == " << S(10000, P) << endl;
	const long long A = S(5678027, P);	
	cout << "S(5678027) == " << A << endl;
	const long long B = S(7208785, P);	
	cout << "S(7208785) == " << B << endl;
	cout << "Sum: " << A + B << endl;
}

long long S(int n, prime &P)
{
	vector<bool> row(n+4, true), up1(n+4, true), up2(n+4, true), down1(n+4, true), down2(n+4, true);
	
	const long long i0 = (((long long)n)*(n-1))/2 + 1;
	const long long iN = i0 + n - 1;
	int i, istart;
	long long ret = 0;

	fillbool(i0, n, row, P);
	fillbool(i0 - n + 1, n - 1, up1, P);
	fillbool(i0 - 2*n + 3, n - 2, up2, P);
	fillbool(i0 + n, n + 1, down1, P);
	fillbool(i0 + 2*n + 1, n + 2, down2, P);
	row[n+2] = false;
	row[n+3] = false;
	up1[n+1] = false;
	up1[n+2] = false;
	up1[n+3] = false;
	up2[n] = false;
	up2[n+1] = false;
	up2[n+2] = false;
	up2[n+3] = false;
	down1[n+3] = false;

	istart = 3 - (i0 % 2);

	for(i = istart; i < n + 2; i += 2)
		if(row[i]) {
			if(up1[i-1] && (row[i-2] || up2[i-1] || up1[i+1] || down1[i])) {
				ret += i0 + i - 2;
				continue;
			}

			if(up1[i] && (up2[i-1] || up2[i+1] || down1[i-1] || down1[i+1])) {
				ret += i0 + i - 2;
				continue;
			}

			if(up1[i+1] && (row[i+2] || up2[i+1] || down1[i])) {
				ret += i0 + i - 2;
				continue;
			}
			
			if(down1[i-1] && (row[i-2] || down2[i-1] || down1[i+1])) {
				ret += i0 + i - 2;
				continue;
			}				
		
			if(down1[i] && (down2[i-1] || down2[i+1])) {
				ret += i0 + i - 2;
				continue;
			}

			if(down1[i+1] && (row[i+2] || down2[i+1]))
				ret += i0 + i - 2;
		}

	return ret;
}

void fillbool(long long start, int N, vector<bool> &v, prime &P)
{
	int maxp = floor(sqrt((double) (start + N - 1)));
	int k;
	v[0] = false;
	v[1] = false;
	for(int i = 0; P.p(i) <= maxp; i++)
		for(k = (start % P.p(i)) ? (P.p(i) - start % P.p(i)) : 0; k < N; k += P.p(i)) 
			v[2+k] = false;
}
