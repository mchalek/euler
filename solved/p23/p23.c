#include <stdio.h>
#include <string.h>

int NMAX = 28123;
int PMAX = 14062;

int main(void)
{
    int iscomp[PMAX + 1];
    int isabunsum[NMAX + 1];
    int psums[3500][16];
    int abun[20000];
    int np = 0;
    int i, j, na = 0;
    int s;
    
    memset(iscomp, 0, sizeof(iscomp));
    iscomp[0] = 1;
    iscomp[1] = 1;
    int r;

    for(i = 2; i < PMAX; i++) {
        if(!iscomp[i]) {
            psums[np][0] = 1;
            r = 1;
            for(j = 1; j < 16; j++) {
                psums[np][j] = psums[np][j-1] + r*i;
                r *= i;
            }

            np++;

            j = 2*i; 
            while(j < PMAX) {
                iscomp[j] = 1;
                j += i;
            }
        }
    }

    int itmp;
    for(i = 2; i < NMAX; i++) {
        itmp = i;
        s = 1;
        for(j = 0; j < np && itmp > 1; j++) {
            int k = 0;
            while(!(itmp % (psums[j][1]-1))) {
                itmp /= (psums[j][1]-1);
                k++;
            }
            s *= psums[j][k];
        }
        if(itmp == 1)
            s -= i;
        if(s > i)
            abun[na++] = i;
    }
    
    memset(isabunsum, 0, sizeof(isabunsum));
    for(i = 0; i < na; i++) {
        for(j = i; j < na; j++) {
            int ix = abun[i] + abun[j];
            if(ix <= NMAX)
                isabunsum[abun[i] + abun[j]] = 1;
        }
    }

    s = 0;
    for(i = 1; i < NMAX; i++)
        if(!isabunsum[i])
            s += i;
    
    printf("%d\n", s);

    return 0;
}
