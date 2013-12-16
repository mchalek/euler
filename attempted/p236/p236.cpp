#include<cstdio>

int main(void)
{
	int NA[] = {5248, 1312, 2624, 5760, 3936};
	int NB[] = {640, 1888, 3776, 3776, 5664};

	int sa[5], sb[5]; // number spoiled

	int i, j;
	double m;

	for(i = 1; i < NA[1]; i++) {
		sa[1] = i;
		for(j = 1; j < NB[1]; j++) {
			sb[1] = j;
			m = (((double) i) * NB[1]) / (j * NA[i]);
			
//			sa[0] = 

		}
	}
}