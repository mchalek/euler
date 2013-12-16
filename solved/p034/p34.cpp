#include<iostream>

#define UB 2540160 // very weak upper bound, equal to 9!*7

int factorial(int);
int digits(int, int[]);

int main(void)
{
	int fn, j, sum=0, ndig;
	int dig[7];
	for(int i = 3; i < UB; i++) {
		ndig = digits(i, dig);
		fn = 0;
		for(j = 0; j < ndig; j++)
			fn += factorial(dig[j]);
		if(i == fn) {
			std::cout << i << " is one such number.\n";
			sum += i;
		}
	}

	std::cout << "Sum of all these numbers: " << sum << std::endl;
	return 0;
}

int digits(int n, int dig[])
{
	int i = 0;
	memset(dig, 0, 7*sizeof(int));
	while(n > 0) {
		dig[i++] = n % 10;
		n /= 10;
	}

	return i;
}

int factorial(int n)
{
	if(!n) 
		return 1;
	else
		return factorial(n-1)*n;
}