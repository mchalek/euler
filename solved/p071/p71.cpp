#include<iostream>
using namespace std;

int main(void)
{
	long long ntest, d;
	long long nsol = 0, dsol = 1;
	for(d = 1000000; d > 2; d--) { // could probably stop at a much bigger value...
		ntest = (d % 7) ? 3*d/7 : 3*d/7-1;
		if(ntest*dsol >= nsol*d) { // will automatically find reduced fractions because of >= instead of >
			nsol = ntest;
			dsol = d;
		}
	}
	cout << "Solution: " << nsol << " / " << dsol << endl;
}
