#include<stdio.h>

int main(void)
{
	long long i=1, Nper=0, Ntot=0, nextpern=3;
	
	while(Ntot <= Nper*12345 || Ntot == 0) {
		i++;
		if(!((i*i-1) % 4)) {
			Ntot++;
			if(i == nextpern) {
				Nper++;
				nextpern = 2*(nextpern + 1) - 1;
			}
		}
	}

	printf("k == %lld at finish.\n", (i*i-1)/4);
	printf("Exact fraction: %lld/%lld\n", Nper, Ntot);

	return 0;
}
