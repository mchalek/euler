#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this code is wrong, but close...  I think the issue is not properly
// handling the fixed order of the CC and CH decks.  For the 6-sided die,
// it gets the first 2 squares right, but the third one comes in 5th place.
// But for the 4-sided die, the top 3 squares are correct.
// To get the truly right answers, I had considered doing a simulation
// instead of this master equation approach.  Luckily I ended up not needing
// it.

#define SQUARES 40
#define SIDES 4
#define MAX_ROLL (2*(SIDES))

#define GO 0
#define JAIL 10
#define GTJ 30
#define CC1 2
#define CC2 17
#define CH1 7
#define CH2 22
#define CH3 36

#define C1 11
#define E3 24
#define H2 39
#define R1 5
#define R2 15
#define R3 25
#define R4 35
#define U1 12
#define U2 28

typedef struct {
    int idx;
    double sum;
} idxsum_t;

int cccmp(const void *va, const void *vb)
{
    idxsum_t *a = (idxsum_t *) va;
    idxsum_t *b = (idxsum_t *) vb;

    return (a->sum == b->sum) ? 0 : (1 - 2*(a->sum < b->sum));
}

double pr[1 + MAX_ROLL];
double pd[1 + MAX_ROLL];

void init()
{
    int nr[1 + MAX_ROLL];
    int nd[1 + MAX_ROLL];

    int i, j;
    memset(nr, 0, sizeof(nr));
    memset(nd, 0, sizeof(nd));
    for(i = 1; i <= SIDES; i++) {
        nd[2*i]++;
        for(j = 1; j <= SIDES; j++) {
            nr[i + j]++;
        }
    }

    double rsum = 0;
    for(i = 0; i <= MAX_ROLL; i++) {
        pd[i] = ((double) nd[i]) / (SIDES*SIDES);
        pr[i] = ((double) nr[i]) / (SIDES*SIDES);

        printf("pr[%d] == %g\n", i, pr[i]);
        printf("pd[%d] == %g\n", i, pd[i]);
        rsum += pr[i];
    }

    printf("sum pr == %g\n", rsum);
}

void zero(double p[])
{
    int i;
    for(i = 0; i < SQUARES; i++)
        p[i] = 0.0;
}

double sum(double a[]) {
    double ret = 0.0;
    int i;
    for(i = 0; i < SQUARES; i++)
        ret += a[i];
    return ret;
}

void roll(double p0_0[], double p1_0[], double p2_0[],
          double p0_1[], double p1_1[], double p2_1[]) {
    // pi_j is probability distribution over squares at time j, 
    // given a string of i double rolls
    // naive roll, does not handle any weird cases yet
    zero(p0_1);
    zero(p1_1);
    zero(p2_1);
    int i, j;
    for(i = 0; i < SQUARES; i++) {
        for(j = 2; j <= MAX_ROLL; j++) {
            double p_single = pr[j] - pd[j];
            p0_1[(i + j) % SQUARES] += (p0_0[i] + p1_0[i] + p2_0[i])*p_single; 
            p1_1[(i + j) % SQUARES] += p0_0[i]*pd[j];
            p2_1[(i + j) % SQUARES] += p1_0[i]*pd[j];

            p0_1[JAIL] += p2_0[i]*pd[j];
        }
    }
}

void gtj(double p0[], double p1[], double p2[]) {
    p0[JAIL] += p0[GTJ] + p1[GTJ] + p2[GTJ];
    p0[GTJ] = 0.0;
    p1[GTJ] = 0.0;
    p2[GTJ] = 0.0;
}

int isRR(int x) {
    return (x == R1) || (x == R2) || (x == R3) || (x == R4);
}

int isU(int x) {
    return (x == U1) || (x == U2);
}

int next(int x, int (*test)(int)) {
    while(!test(x)) {
        x++;
        x %= SQUARES;
    }

    return x;
}

void ch(int CH, double p0[], double p1[], double p2[]) {
    p0[GO] += 1.0 / 16 * p0[CH];
    p1[GO] += 1.0 / 16 * p1[CH];
    p2[GO] += 1.0 / 16 * p2[CH];

    p0[JAIL] += 1.0 / 16 * p0[CH];
    p1[JAIL] += 1.0 / 16 * p1[CH];
    p2[JAIL] += 1.0 / 16 * p2[CH];

    p0[C1] += 1.0 / 16 * p0[CH];
    p1[C1] += 1.0 / 16 * p1[CH];
    p2[C1] += 1.0 / 16 * p2[CH];

    p0[E3] += 1.0 / 16 * p0[CH];
    p1[E3] += 1.0 / 16 * p1[CH];
    p2[E3] += 1.0 / 16 * p2[CH];

    p0[H2] += 1.0 / 16 * p0[CH];
    p1[H2] += 1.0 / 16 * p1[CH];
    p2[H2] += 1.0 / 16 * p2[CH];

    p0[R1] += 1.0 / 16 * p0[CH];
    p1[R1] += 1.0 / 16 * p1[CH];
    p2[R1] += 1.0 / 16 * p2[CH];

    int RR = next(CH, isRR);
    p0[RR] += 1.0 / 8 * p0[CH];
    p1[RR] += 1.0 / 8 * p1[CH];
    p2[RR] += 1.0 / 8 * p2[CH];
    
    int UU = next(CH, isU);
    p0[UU] += 1.0 / 16 * p0[CH];
    p1[UU] += 1.0 / 16 * p1[CH];
    p2[UU] += 1.0 / 16 * p2[CH];

    int BB = (CH - 3 + SQUARES) % SQUARES;
    p0[BB] += 1.0 / 16 * p0[CH];
    p1[BB] += 1.0 / 16 * p1[CH];
    p2[BB] += 1.0 / 16 * p2[CH];
    
    p0[CH] *= 3.0 / 8;
    p1[CH] *= 3.0 / 8;
    p2[CH] *= 3.0 / 8;
}

void cc(int CC, double p0[], double p1[], double p2[]) {
    p0[GO] += 1.0 / 16 * p0[CC];
    p1[GO] += 1.0 / 16 * p1[CC];
    p2[GO] += 1.0 / 16 * p2[CC];

    p0[JAIL] += 1.0 / 16 * p0[CC];
    p1[JAIL] += 1.0 / 16 * p1[CC];
    p2[JAIL] += 1.0 / 16 * p2[CC];

    p0[CC] *= 7.0 / 8;
    p1[CC] *= 7.0 / 8;
    p2[CC] *= 7.0 / 8;
}

int main()
{
    init();

    double p0[SQUARES], p1[SQUARES], p2[SQUARES];

    zero(p0);
    zero(p1);
    zero(p2);

    p0[GO] = 1.0;

    int i;
    for(i = 0; i < 10000; i++) {
        double p0_1[SQUARES], p1_1[SQUARES], p2_1[SQUARES];
        roll(p0, p1, p2, p0_1, p1_1, p2_1);

        memcpy(p0, p0_1, sizeof(p0));
        memcpy(p1, p1_1, sizeof(p1));
        memcpy(p2, p2_1, sizeof(p2));

        gtj(p0, p1, p2);
        ch(CH1, p0, p1, p2);
        ch(CH2, p0, p1, p2);
        ch(CH3, p0, p1, p2);
        cc(CC1, p0, p1, p2);
        cc(CC2, p0, p1, p2);
    }

    idxsum_t psum[SQUARES];
    for(i = 0; i < SQUARES; i++) {
        psum[i].idx = i;
        psum[i].sum = p0[i] + p1[i] + p2[i];
    }
    qsort(psum, SQUARES, sizeof(idxsum_t), cccmp);

    printf("modal string: %02d%02d%02d%02d%02d%02d%02d\n",
            psum[SQUARES-1].idx,
            psum[SQUARES-2].idx,
            psum[SQUARES-3].idx,
            psum[SQUARES-4].idx,
            psum[SQUARES-5].idx,
            psum[SQUARES-6].idx,
            psum[SQUARES-7].idx);

    printf("modal probabilities: %g, %g, %g, %g, %g, %g, %g\n", 
            psum[SQUARES-1].sum,
            psum[SQUARES-2].sum,
            psum[SQUARES-3].sum,
            psum[SQUARES-4].sum,
            psum[SQUARES-5].sum,
            psum[SQUARES-6].sum,
            psum[SQUARES-7].sum);

    printf("JAIL: %g\n", p0[JAIL] + p1[JAIL] + p2[JAIL]);
    printf("E3: %g\n", p0[E3] + p1[E3] + p2[E3]);
    printf("GO: %g\n", p0[GO] + p1[GO] + p2[GO]);

    printf("SUM: %g\n", sum(p0) + sum(p1) + sum(p2));

    return 0;
}
