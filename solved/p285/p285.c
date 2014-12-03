#include <math.h>
#include <stdio.h>

#define N 100000

// find the area of annular region via polar integral
// difficulty only appears due to incompatible symmetry at the xy axes.
// let the angles theta1 and theta0 be the angles at which the boundaries of
// the annulus hit the x axis.  Then for theta1 < theta < theta0, the
// integration radius is bounded above by (k+0.5)^2 and below by 1/sin(theta).
// This integrates cleanly and we're left just doing the computation.

double p(int k) {
    double dk = k;
    double r0 = k - 0.5;
    double r0_2 = r0*r0;

    double r1 = k + 0.5;
    double r1_2 = r1*r1;

    double theta0 = asin(1.0 / r0);
    double theta1 = asin(1.0 / r1);

    double A0 = (M_PI/4 - theta0)*(r1_2 - r0_2);
    double A1 = (theta0 - theta1)*r1_2 + sqrt(r0_2 - 1) - sqrt(r1_2 - 1);
    if(k == 1) {
        A0 = 0.0;
        theta0 = M_PI/4;
        A1 = (theta0 - theta1)*r1_2 + 1 - sqrt(r1_2 - 1);
    }

    return (A0 + A1) / (dk*dk);
}

int main()
{
    int k;

    double Es = 0;
    for(k = 1; k <= N; k++) {
        Es += k*p(k);
        //printf("p(%g) == %g; Es[%g] == %g\n", (double) k, p(k), (double) k, Es);
    }

    printf("expected score: %.5f\n", Es);

    return 0;
}
