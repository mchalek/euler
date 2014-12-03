#include <math.h>
#include <stdio.h>

#define N 100000

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
        A1 = (theta0 - theta1)*r1_2 + 1/tan(theta0) - 1/tan(theta1);
    }

    return (A0 + A1) / (dk*dk);
}

int main()
{
    int k;

    double Es = 0;
    for(k = 1; k <= N; k++) {
        Es += k*p(k);
        printf("p(%g) == %g; Es[%g] == %g\n", (double) k, p(k), (double) k, Es);
    }

    printf("expected score: %.5f\n", Es);
}
