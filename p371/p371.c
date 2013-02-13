#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("SYNTAX: %s niter\n", argv[0]);
        exit(0);
    }
    int niter = atoi(argv[1]);

    double p[1001];
    int i, j;
    double h = 1;
    double g = 0;
    double ans = 0;

    for(i = 0; i <= 1000; i++) {
        p[i] = 0.0;
    }
    p[0] = 1.0/1000; // could have drawn all zero plate
    p[1] = 999.0/1000.0;

    // at this point p reflects the distribution of uniq counts after
    // one trial,
    // h is the probability that no pair sums to 1000 (for 1 trial, so h == 1)

    for(i = 0; i < niter; i++) {
#if 1
        double psum = g;
        for(j = 0; j <= 999; j++) {
            psum += p[j];
        }
        if(fabs(1.0-psum) > 1e-8)
            printf("psum [%d]: %.10f\n", i, psum);
        printf("p: %.4f %.4f %.4f %.4f %.4f %.4f\n", 
                p[0], p[1], p[2], p[3], p[4], p[5]);
#endif

        // now update distribution
        double ptmp[1001];
        memcpy(ptmp, p, sizeof(ptmp));
        p[0] = ptmp[0]*1.0/1000.0;
        double gtmp = g;
        for(j = 1; j <= 999; j++) {
            g += ptmp[j]*j/1000.0;

            p[j] += ptmp[j-1]*(999.0-j)/1000.0  // j-1 -> j
                   - ptmp[j]*j/1000.0 // j -> success
                   - ptmp[j]*(998.0-j)/1000.0; // j -> j+1
#if 0
            p[j] += ptmp[j]*(j+1.0)/1000.0 // j -> j
                   + ptmp[j-1]*(999.0-j)/1000.0  // j-1 -> j
                   - ptmp[j]*j/1000.0;
#endif
        }
        double delg = g-gtmp;
        ans += (2+i)*delg;
    }
    printf("after iteration %d: h == %g, ans == %.8f\n", i, h, (double) ans);

    return 0;
}
