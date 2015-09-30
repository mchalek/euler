#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <prime.h>

#define N 5000

long np;
long *p;

typedef struct {
    long a, b;
} point_t;

typedef struct {
    point_t p0;
    point_t p1;
} segment_t;

#define NEXT(a) (((a)*(a)) % 50515093)

void generate(int num_segments, segment_t segments[])
{
    long s[] = {0,0,0,290797};

    int i;
    for(i = 0; i < num_segments; i++) {
        s[0] = NEXT(s[3]);
        s[1] = NEXT(s[0]);
        s[2] = NEXT(s[1]);
        s[3] = NEXT(s[2]);

        segments[i].p0.a = s[0] % 500;
        segments[i].p0.b = s[1] % 500;
        segments[i].p1.a = s[2] % 500;
        segments[i].p1.b = s[3] % 500;
    }
}

#define ABS(a) (((a) > 0) ? (a) : (-(a)))
bool check_st(long num, long den) {
    if(!num || !den)
        return false;

    if(num > 0 && den > 0) {
        return num < den;
    } else if((num < 0 && den > 0) || (num > 0 && den < 0)) {
        return false;
    } else {
        return num > den;
    }

    // not reachable
    return false;
}

bool check(segment_t *s0, segment_t *s1, segment_t *intersection)
{
    long a,b,c,d,e,f,g,h;
    a = s0->p0.a;
    b = s0->p0.b;
    c = s0->p1.a;
    d = s0->p1.b;
    e = s1->p0.a;
    f = s1->p0.b;
    g = s1->p1.a;
    h = s1->p1.b;

    long t_numerator = (c-g)*(f-h) - (d-h)*(e-g);
    long t_denominator = (b-d)*(e-g) - (a-c)*(f-h);

    if(!check_st(t_numerator, t_denominator))
        return false;

    long s_numerator = 0;
    long s_denominator = 0;
    if(e == g) {
        s_numerator = t_numerator * (b-d) + t_denominator*(d-h);
        s_denominator = t_denominator * (f-h);
    } else {
        s_numerator = t_numerator * (a-c) + t_denominator*(c-g);
        s_denominator = t_denominator * (e-g);
    }

    if(!check_st(s_numerator, s_denominator))
        return false;

    long x_numerator = ABS(t_numerator * a + (t_denominator - t_numerator)*c);
    long y_numerator = ABS(t_numerator * b + (t_denominator - t_numerator)*d);

    reduce(x_numerator, ABS(t_denominator), np, p, &(intersection->p0.a), &(intersection->p0.b));
    reduce(y_numerator, ABS(t_denominator), np, p, &(intersection->p1.a), &(intersection->p1.b));

    return true;
}

inline bool same_fraction(point_t *a, point_t *b) {
    return b->b*a->a == a->b*b->a;
}

inline bool same_point(segment_t *a, segment_t *b) {
    return same_fraction(&(a->p0), &(b->p0)) && same_fraction(&(a->p1), &(b->p1));
}

int main(void) {
    primes(10000000, &p, &np);
    segment_t *segments = malloc(N*sizeof(segment_t));

    int nalloc = 1 << 20;
    int n_intersections = 0;
    segment_t *intersections = malloc(nalloc*sizeof(segment_t));

    segment_t s0,s1;
    s0.p0.a = 46;
    s0.p0.b = 53;
    s0.p1.a = 17;
    s0.p1.b = 62;

    s1.p0.a = 46;
    s1.p0.b = 70;
    s1.p1.a = 22;
    s1.p1.b = 40;

    segment_t i0;
    bool z = check(&s0, &s1, &i0);
    /*
    if(!z) {
        printf("FAIL\n");
    } else {
        printf("%ld/%ld, %ld/%ld\n", i0.p0.a, i0.p0.b, i0.p1.a, i0.p1.b);
    }

    return 0;
*/
    generate(N, segments);

    int i;
    for(i = 0; i < N; i++) {
        int j;
        for(j = 1 + i; j < N; j++) {
            bool hit = check(segments + i, segments + j, intersections + n_intersections);

            if(!hit)
                continue;

            printf("%ld/%ld\t%ld/%ld\n",
                    intersections[n_intersections].p0.a, 
                    intersections[n_intersections].p0.b, 
                    intersections[n_intersections].p1.a, 
                    intersections[n_intersections].p1.b);

            n_intersections++;
            if(n_intersections == nalloc) {
                nalloc <<= 1;
                intersections = realloc(intersections, nalloc*sizeof(segment_t));
            }
        }
    }

    printf("%d total hits (including duplicates)\n", n_intersections);

    return 0;
}
