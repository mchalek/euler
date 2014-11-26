#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int nsteps;
    if(argc < 2) {
        nsteps = 1000;
    } else {
        nsteps = atoi(argv[1]);
    }

    double p[100][100];
    double q[100][100];
    memset(p, 0, sizeof(p));

    p[0][50] = 1.0;

    double result = 0.0;

    int i;
    for(i = 0; i < nsteps; i++) {
        int j, k;
        memcpy(q, p, sizeof(q));
        memset(p, 0, sizeof(p));
        // duh, update distance instead of pairwise positions
        for(j = 0; j < 100; j++) {
            // j is position of die 0
            int jleft = (100 + j - 1) % 100;
            int jright = (j + 1) % 100;
            for(k = 0; k < 100; k++) {
                // k is position of die 1
                int kleft = (100 + k - 1) % 100;
                int kright = (k + 1) % 100;

                p[jleft][kleft] += q[j][k] / 36.0;
                p[jleft][k] += q[j][k] / 9.0;
                p[jleft][kright] += q[j][k] / 36.0;

                p[j][kleft] += q[j][k] / 9.0;
                p[j][k] += q[j][k] * 4.0 / 9.0;
                p[j][kright] += q[j][k] / 9.0;

                p[jright][kleft] += q[j][k] / 36.0;
                p[jright][k] += q[j][k] / 9.0;
                p[jright][kright] += q[j][k] / 36.0;
            }
        }

        for(j = 0; j < 100; j++) {
            result += i*p[j][j];
            p[j][j] = 0.0;
        }
    }

    printf("result: %g\n", result);
    return 0;
}
