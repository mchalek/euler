#include<iostream>
#include<cstdlib>
using namespace std;

const int twopows[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};
const int ntwopow = 20;

bool ispalin2(int n)
{
	int k = ntwopow;
	int m = 0;
	while(!(n&twopows[--k]));

	while(k > m && ((n&twopows[k] && n&twopows[m]) || (!(n&twopows[k]) && !(n&twopows[m])))) {
		m++;
		k--;
	}
	return k <= m ? 1 : 0;
}

int main(int argc, char ** argv)
{
	int sum = 0;
	for(int a = 1; a < 10; a++) {
		sum += ispalin2(a) ? a : 0;
		sum += ispalin2(11*a) ? 11*a : 0;
		for(int b = 0; b < 10; b++) {
			sum += ispalin2(101*a+10*b) ? 101*a+10*b : 0;
			sum += ispalin2(1001*a+110*b) ? 1001*a+110*b : 0;
			for(int c = 0; c < 10; c++) {
				sum += ispalin2(10001*a+1010*b+100*c) ? 10001*a+1010*b+100*c : 0;
				sum += ispalin2(100001*a+10010*b+1100*c) ? 100001*a+10010*b+1100*c : 0;	
			}
		}
	}

	cout << "p36 sum: " << sum << endl;	
	return 0;
	
}

