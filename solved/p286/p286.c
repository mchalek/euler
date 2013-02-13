#include <stdio.h>
#include <string.h>

double compute_prob(double q)
{
    double pn[51];
    double ptmp[51];
    int i, j;
    for(i = 0; i < 51; i++) {
        pn[i] = 0.0;
    }

    // fill in known value for first shot
    pn[0] = 1.0/q;
    pn[1] = 1.0 - pn[0];

    for(i = 2; i < 51; i++) {
        double pmiss = ((double) i) / q;

        for(j = 0; j < 51; j++)
            ptmp[j] = 0.0;

        ptmp[0] = pn[0]*pmiss;

        for(j = 1; j < 51; j++) {
            ptmp[j] = pn[j]*pmiss + pn[j-1]*(1-pmiss);
        }

        memcpy(pn, ptmp, sizeof(pn));
    }

    return pn[20];
}

int main(void)
{
    // binary search for q, lots of iterations to be safe
    int i;
    double qmax = 61.0;
    double qmin = 51.0;
    double qtest;
    double ptest;
    for(i = 0; i < 100; i++) {
        qtest = (qmin+qmax)/2.0;
        ptest = compute_prob(qtest);
        if(ptest > 0.02) {
            qmin = qtest;
        } else {
            qmax = qtest;
        }
    }
    printf("q == %.10f\n", qtest);


    return 0;
}
