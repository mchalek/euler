#include <stdio.h>

// direct generation of piles
long countPile(int num_left, int max_count)
{
    if(!num_left)
        return 1;
    long ret = 0;
    int stop = (num_left < max_count) ? num_left : max_count;
    int i;
    for(i = 1; i <= stop; i++)
            ret += countPile(num_left - i, i);

    return ret;
}

int main(void)
{
	int maxN = 1000;

	printf("countPile(5) == %ld\n", countPile(5,5));
	long mod = 1000000;
	int z = 6;
	long x = countPile(z,z);

	while(x % mod) {
		printf("not %d (%ld)!\n", z, x);
		z++;
		x = countPile(z,z);
	}

	printf("solution: %d => %ld\n", z, x);
	return 0;
}
