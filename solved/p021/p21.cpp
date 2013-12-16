#include<cstdio>
#include<cstdlib>
#include<cmath>

int pdivsum(int);

int main(void)
{
	int amicable_sum = 0;
	int da, db;

	for(int i = 2; i < 10000; i++) {
		da = pdivsum(i);
		db = pdivsum(da);
		if(i == db && i != da) {
			printf("amicable numbers: %d, %d\n", i, da);
			amicable_sum += i + da;	
		}
	}

	amicable_sum /= 2;
	printf("amicable sum: %d\n", amicable_sum);

	return 0;

}

int pdivsum(int n)
{
	int ret, max_check; 
	if(n == 1)
		return 0;
	if(n == 2)
		return 1;

	ret = 1; // for 1
	max_check = (int) ceil(sqrt((double) n));

	for(int i = 2; i < max_check; i++)
		if(n % i == 0)
			ret += i + n/i;

	return ret;
}