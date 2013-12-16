#include<cstdio>
#include<cstring>

#define EXPONENT 7830457

int main(void)
{
	int i, j, maxI;
	unsigned long long Ans;

	Ans = 1;
	j = EXPONENT % 20;
	for(i = 0; i < j; i++)
		Ans *= 2;

	maxI = EXPONENT/20;
	for(i = 0; i < maxI; i ++) {
		Ans *= 1048576;
		Ans %= 10000000000;
	}
	
	Ans *= 28433;
	Ans += 1;

	printf("Last ten digits: %lld\n", Ans % 10000000000);
	return 0;
}