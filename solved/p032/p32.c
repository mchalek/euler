#include <stdio.h>
#include <inttypes.h>

uint16_t getdigs(int x, int *numrep)
{
    uint16_t ret = 0;
    while(x) {
        int d = x % 10;
        (*numrep) += 1 & (ret >> d);
        ret |= 1 << d;
        x /= 10;
    }
    return ret;
}


int main(void)
{
    int a, b;
    int sum = 0;
    for(a = 1; a < 10000; a++) {
        int numrep = 0;
        uint16_t adigs = getdigs(a, &numrep);
        if(numrep)
            continue;
        if(adigs & 1)
            continue;
        for(b = a; b < 10000; b++) {
            int numrep = 0;
            uint16_t bdigs = getdigs(b, &numrep);

            if(numrep)
                continue;
            if(bdigs & adigs)
                continue;
            if(bdigs & 1)
                continue;

            uint16_t cdigs = getdigs(a*b, &numrep);
            if(numrep)
                continue;

            if(cdigs & (adigs | bdigs))
                continue;

            if(0x3fe == ((adigs | bdigs) | cdigs)) {
                sum += a*b;
                printf("%d * %d == %d\n", a, b, a*b);
            }
        }
    }
    
    printf("sum: %d\n", sum);
}
