#include<iostream>

#define UB 354294 // very weak upper bound, equal to 9^5*6

void digits(int, int[]);

int main(void)
{
	int pow5, j, sum=0;
	int dig[6];
	for(int i = 2; i < UB; i++) {
		digits(i, dig);
		pow5 = 0;
		for(j = 0; j < 6; j++)
			pow5 += dig[j]*dig[j]*dig[j]*dig[j]*dig[j];
		if(i == pow5) {
			std::cout << i << " is one such number.\n";
			sum += i;
		}
	}

	std::cout << "Sum of all these numbers: " << sum << std::endl;
	return 0;
}

void digits(int n, int dig[])
{
	int i = 0;
	memset(dig, 0, 6*sizeof(int));
	while(n > 0) {
		dig[i++] = n % 10;
		n /= 10;
	}

	return;
}