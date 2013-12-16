#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char ** argv)
{
	if(argc != 2)
		printf("Error: Input argument required!\n");
	else {
		const int Nmax = atoi(argv[1]);
		
		long long a, a2, a3, q, b, c;
		long long tmp, bMax, bMin;
		double diff;
		int count = 0;

		for(a = 2; a <= Nmax; a+=3LL) {
			a2 = a*a;
			a3 = a2*a;
			q = (8*a3+15*a2+6*a-1)/27;
			
			tmp = (long long) floor(sqrt((double) q));
			bMax = tmp < Nmax - a - 1 ? tmp : Nmax - a - 1;
			tmp = (long long) floor(sqrt((double) q / Nmax));
			bMin = tmp > 1 ? tmp : 1;
			for(b = bMin; b <= bMax; b++) {
				if(!(q % b*b)) {
					c = q / (b*b);	
					diff = fabs(pow(((double) a) + b*sqrt((double) c), 1.0/3.0) - pow(b*sqrt((double)c) - ((double) a), 1.0/3.0) - 1.0);
					count += (a+b+c <= Nmax) && diff < 1e-10;
					//if(diff < 1e-5 && a + b + c <= Nmax)
					//	printf("Suspected triplet: (%d, %d, %d); q == %d\n", a, b, c, q);
				}
			}
		}
		
		printf("Counted: %d\n", count);
	}
	return 0;
}
