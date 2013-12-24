#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double q[101][101];

double qnm(int n, int m, int T) {
    if(n == 100)
        return 0.;

    if(m >= 100)
        return 0.;

    int T2 = 1 << T;
    int m2 = m + T2/2;

    if(n < 99 && m2 < 100) {
        return (q[n][m2] + q[n+1][m2] + (T2-1)*q[n+1][m]) / (T2 + 1);
    } else if(n == 99 && m2 < 100) {
        return q[n][m2] / (T2 + 1);
    } else if(n < 99 && m2 >= 100) {
        return (2.0 + (T2-1)*q[n+1][m]) / (T2 + 1);
    } else if(n == 99 && m2 >= 100) {
        return 2.0 / (T2 + 1);
    } else *((int *) NULL) = 1;

    return -1;
}

double get_best_q(int n, int m) {
    int T;
    //int best_T = 0;
    double best_q = 0.0;
    T = 0;
    do {
        T++;
        double test_q = qnm(n, m, T);

        if(test_q > best_q) {
            best_q = test_q;
            //best_T = T;
        }
    } while(m + (1 << (T-1)) < 100);

    //printf("T(%d,%d) == %d\n", n, m, best_T);
    return best_q;
}

int main(void) {
    int n, m;
    for(n = 0; n < 101; n++)
        for(m = 0; m <= 101; m++)
            q[n][m] = INFINITY;

    for(n = 0; n < 101; n++) {
        q[100][n] = 0.0;
        q[n][100] = 1.0;
    }
    q[100][100] = INFINITY;

    for(n = 99; n >= 0; n--) {
        m = 99;
        q[n][m] = 2.0/3.0 * (1.0 + 0.5*q[n+1][99]);
    }

    for(n = 99; n >= 0; n--) {
        for(m = 98; m >= 0; m--) {
            q[n][m] = get_best_q(n, m);
        }
    }

    /*
    for(n = 100; n >= 0; n--)
        for(m = 100; m >= 0; m--)
            printf("q(%d,%d) == %g\n", n, m, q[n][m]);
*/
    printf("solution: %.8f\n", 0.5*(q[1][0] + q[0][0]));

    return 0;
}
