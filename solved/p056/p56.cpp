#include<iostream>
#include<cstring>
using namespace std;

int main(void)
{
	int a0;
	int maxa = 0;
	int maxb = 0;
	int maxsum = 0;
	int digits[200];
	int dsum;
	int carry;
	int prod;

	int AMIN = 2;
	int AMAX = 100;
	int BMAX = 100;


	for(int a = AMIN; a <= AMAX; a++) {
		memset(digits, 0, 200*sizeof(int));
		a0 = a;
		for(int k = 0; k < 3; k++) {
			digits[k] = a0 % 10;
			a0 /= 10;
		}
			
		for(int b = 2; b <= BMAX; b++) {
			carry = 0;
			for(int l = 0; l < 200; l++) {
				prod = digits[l]*a + carry;
				digits[l] = prod % 10;
				carry = prod / 10;
			}

			dsum = 0;
			for(int j = 0; j < 200; j++)
				dsum += digits[j];

			//cout << a << "^" << b << " => " << dsum << endl;
			if(dsum > maxsum) {
				maxsum = dsum;
				maxa = a;
				maxb = b;
			}
		}
	}

	cout << maxa << "^" << maxb << " yields digital sum " << maxsum << endl;

}