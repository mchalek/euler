#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int nsteps;
    if(argc < 2) {
        nsteps = 100000;
    } else {
        nsteps = atoi(argv[1]);
    }

    double p[51];
    double q[51];
    memset(p, 0, sizeof(p));

    p[50] = 1.0;

    double result = 0.0;

    int i;
    for(i = 0; i < nsteps; i++) {
        int j;
        memcpy(q, p, sizeof(q));
        memset(p, 0, sizeof(p));

        for(j = 1; j < 51; j++) {
            // first handle the case where the two dice move
            // toward each other, i.e. in the direction that reduces
            // distance
            double x = q[j] / 36.0; // * (1/6 * 1/6);
            if(j == 1) {
                // if j == 1, then the two dice swap positions,
                // so distance stays the same
                p[1] += x;
            } else {
                // otherwise distance goes down by 2
                p[j-2] += x;
            } 

            // next do the case where 1 die stays in place, the other
            // moves toward it.  There are 2 ways this can happen,
            // since there are 2 die
            x = q[j] * 2.0 / 9.0; // * 2 * (4/6 * 1/6);
            p[j-1] += x;

            // now the case where distance remains the same.  This can either
            // happen by both dies not moving, or by both of them moving
            // in the same direction.  This latter case has 2 possibilities,
            // because there are 2 directions
            x = q[j] / 2.0; // * (4/6 * 4/6 + 2 * 1/6 * 1/6);
            p[j] += x;

            // final cases: 
            // 1) 1 die stays in place and the other moves away from it,
            //    increasing distance by 1
            // 2) 2 dies move away from each other, increasing distance
            //    by 2
            x = q[j] * 2.0 / 9.0; // * 2 * (4/6 * 1/6);
            double y = q[j] / 36.0; // * (1/6 * 1/6);

            if(j == 49) {
                p[50] += x;
                p[49] += y;
            } else if(j == 50) {
                p[49] += x;
                p[48] += y;
            } else {
                p[j+1] += x;
                p[j+2] += y;
            }
        }

        double sum = 0.0;
        for(j = 0; j < 51; j++)
            sum += p[j];

        double delta_p = p[0];
        result += (1+i)*delta_p;
    }

    printf("result: %.10lf\n", result);
    return 0;
}
