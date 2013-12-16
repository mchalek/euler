#include<cstdio>
#include<cstring>

#define FACTORIAL 100

int main(void)
{
	int digits[400];
	memset(digits, 0, 400*sizeof(int));
	int ndig=1, i, j, carry;
	int digsum = 0;

	digits[0] = 1;

	for(i = 2; i <= FACTORIAL; i++) {
		carry = 0;
		for(j=0; j < ndig; j++) {
			digits[j] *= i;
			digits[j] += carry;
			
			carry = digits[j] / 10;
			digits[j] %= 10;
			if(j + 1 == ndig)
				if(carry > 100)
					ndig += 3;
				else
					if(carry > 10)
						ndig += 2;
					else
						if(carry)
							ndig++;
				
		}
	}
	for(i = 0; i < ndig; i++)
		digsum += digits[i];

	printf("Sum of digits: %d\n", digsum);
}