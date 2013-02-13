#include<iostream>
#include<cmath>

int main(void)
{
	int count = 0; // for 1^1
	int n;
	double x;

	for(int k = 1; k < 10; k++) {
		x = log10((double) k);
		n = 1;
		while(1/(1-x) >= (double) n) {
			std::cout << k << "^" << n << " has " << n << " digits\n";
			n++;
			count++;
		}
	}

	std::cout << "count: " << count << std::endl;
	return 0;
}
