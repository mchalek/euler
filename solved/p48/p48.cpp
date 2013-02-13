#include<iostream>
#include<cstdio>
using namespace std;

int main(void)
{
	unsigned long long last10 = 0;
	unsigned long long currprod = 0;

	for(unsigned long long n = 1; n <= 1000; n++) {
		currprod = n;
		for(int k = 2; k <= n; k++) {
			currprod *= n;
			currprod %= 10000000000LLU;
		}		
		last10 += currprod;
		last10 %= 10000000000LLU;
	}
	cout << "p48 last 10 digits of sum == " << last10 << "\n";

	return 0;			
}
