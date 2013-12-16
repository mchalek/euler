#include<cstdio>

#define YMIN 10000000
#define YMAX 14000000
int main(void)
{
	unsigned long long N, M;
	unsigned long long y;

	int k;
	bool found = false;
	unsigned long long Ans, NAns;

	y = YMIN; 
	while(y <= YMAX && !found) {
		N = (10*y+3)*(10*y+3);
		M = N / 100; // we know it ends in 9 already
		k = 8;

		while(M % 10 == k) {
			k--;
			M /= 100;
		}
		if(!M) {
			found = true;
			Ans = 100*y+30;
			NAns = N;
		}
		
		N = (10*y+7)*(10*y+7);
		M = N / 100; // we know it ends in 9 already
		k = 8;

		while(M % 10 == k) {
			k--;
			M /= 100;
		}
		if(!M) {
			found = true;
			Ans = 100*y+70;
			NAns = N;
		}
		y++;
	}

	printf("I stopped looking after finding %lld, the square of %lld\n", NAns, Ans);
	return 0;
}