#include<iostream>
#include<cmath>
using namespace std;

int main(void)
{
	int Nint = 0;
	int M = 1, xpy, z;
	int x, y;
	int D2;

	//while(M < 1000) {
	while(Nint < 1000000) {
		M++;
		z = M;
		// Just add on all possibilities with z=M, x <= M, y <= M
		// (Since x <= y <= z eliminates duplicate boxes)
		for(xpy = 2; xpy <= 2*M; xpy++) {
			D2 = xpy*xpy + z*z;
			if(floor(sqrt(D2)) == sqrt(D2))
				Nint += xpy/2 -((0 > xpy - M) ? 0 : xpy - M - 1); // # of ways to make x+y=xpy
		}
	}

	cout << "Nint == " << Nint << " when M == " << M << endl;
/* // Brute force for checking, though it is not too slow to complete problem
	Nint = 0;
	M = 1000;
	for(x = 1; x <= M; x++)
		for(y = x; y <= M; y++)
			for(z = y; z <= M; z++) {
				D2min = (x+y)*(x+y) + z*z;
				if(floor(sqrt(D2min)) == sqrt(D2min))
					Nint++;	
			}
				
	cout << "Nint == " << Nint << " when M == " << M << endl;
*/
	return 0;
}
