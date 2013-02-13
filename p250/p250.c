#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long ipow(unsigned long x, unsigned long y, unsigned long mod)
{
    unsigned long squares[64];
    unsigned long ret = 1;
    squares[0] = x % mod;
    
    int i, j;
    for(i = 1; i < 64; i++) {
        squares[i] = (squares[i-1] * squares[i-1]) % mod;
    }

    for(i = 63; i >= 0; i--) {
        int count = y / (1ul << i);
        for(j = 0; j < count; j++) {
            ret *= squares[i];
            ret %= mod;
        }
        y %= (1ul << i);
    }

    return ret;
}

void dosums(const unsigned long sumsj[250], const unsigned long sums1[250], 
        unsigned long sumsk[250], int k)
{
    int i, j;
    
    memset(sumsk, 0, sizeof(sumsk));
    for(i = 0; i < 250; i++) {
        for(j = 0; j < 250; j++) {
            int sum = (i + j) % 250;
            if(k == 2 && i == j && sums1[j])
                sumsk[sum] += sumsj[i]*(sums1[j]-1);
            else
                sumsk[sum] += sumsj[i]*sums1[j];
        }
    }

    for(i = 0; i < 250; i++) {
        sumsk[i] /= k;
        sumsk[i] %= 10000000000000000ul;
    }
}

int main(void)
{
    int i, j;
    unsigned long sums[250];
    unsigned long prodsums[250];

    // relevant quantity is numbers of sets that 
    // sum to different amounts mod 250
    memset(sums, 0, sizeof(sums));
    for(i = 1; i < 250251; i++) {
        sums[ipow(i, i, 250)]++;
    }

    unsigned long ans = sums[0];
    memcpy(prodsums, sums, sizeof(sums));
    unsigned long tmp[250];
    for(i = 2; i <= 250250; i++) { 
        dosums(prodsums, sums, tmp, i);
        ans += prodsums[0];
        ans %= 10000000000;
        if(!(i % 100))
            printf("%d done.\n", i);
        memcpy(prodsums, tmp, sizeof(tmp));
    }
    printf("prodsums: \n");
    for(i = 0; i < 250; i++)
        printf("%3d: %ld\n", i, prodsums[i]);
    printf("ans: %ld\n", ans);
}
