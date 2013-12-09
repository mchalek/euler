#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
using namespace std;

int main(void)
{
	int issquare[1001];
	memset(issquare, 0, 1001*sizeof(int));
	for(int i = 1; i < 32; i++)
		issquare[i*i] = 1;

	int Dsol = 2;
	long long ysol = 1;
	long long xsol = 1;
	long long x, y, q;
	
	for(long long D = 4; D < 100; D++) {
		if(!issquare[D]) {
			x = D - 2;
			y = 1;
			q = x*x - D*y*y - 1;
			while(q) {
				if(q > 0) 
					y++;
				else
					x++;
				q = x*x - D*y*y - 1;
			}
			if(y > ysol) {
				ysol = y;
				xsol = x;
				Dsol = D;
			}
			cout << "(" << x << ", " << y << ", " << D << ")\n";
		}
	} 
	cout << "Solution: " << xsol << "^2 - " << Dsol << "*" << ysol << "^2 == 1\n"; 
	cout << "Optimal D: " << Dsol << endl;
	return 0;
}
