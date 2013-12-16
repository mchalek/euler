#include<cstdio>
#include<cstring>

#define SUMLEN 1000

int main(void)
{
	int digits0[1001];
	int digits1[1001];
	int digitstmp[1001];
	memset(digits1, 0, 1001*sizeof(int));
	memset(digits0, 0, 1001*sizeof(int));
	memset(digitstmp, 0, 1001*sizeof(int));
	int ndig0=1, ndig1=1, i, j, carry, n;
	int digsum = 0;

	digits0[0] = 1;
	digits1[0] = 1;

	n = 2;
	while(ndig1 < SUMLEN) {
		n++;
		carry = 0;
		memcpy(digitstmp, digits0, ndig0*sizeof(int));
		memcpy(digits0, digits1, ndig1*sizeof(int));
		ndig0 = ndig1;
		for(j=0; j < ndig1; j++) {
			digits1[j] += digitstmp[j] + carry;
			
			carry = digits1[j] / 10;
			digits1[j] %= 10;
			if(j + 1 == ndig1 && carry)
				ndig1++;
		}
	}
	/*for(i = 0; i < ndig1; i++)
		printf("%d  ", digits1[ndig1-i-1]);
*/
	printf("\n");
	printf("This is term number %d\n", n);
}