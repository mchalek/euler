#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <prime.h>

#define N 5000

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

    // encode rational (x, y) intersection as a pair of points
    intersection->p0.a = x_numerator;
    intersection->p0.b = ABS(t_denominator);
    intersection->p1.a = y_numerator;
    intersection->p1.b = ABS(t_denominator);

    return true;
}

inline bool same_fraction(point_t *a, point_t *b) {
    return b->b*a->a == a->b*b->a;
}

inline bool same_point(segment_t *a, segment_t *b) {
    return same_fraction(&(a->p0), &(b->p0)) && same_fraction(&(a->p1), &(b->p1));
}

int main(void) {
    segment_t *segments = malloc(N*sizeof(segment_t));

    int nalloc = 1 << 20;
    int n_intersections = 0;
    segment_t *intersections = malloc(nalloc*sizeof(segment_t));

    generate(N, segments);

    int i;
    for(i = 0; i < N; i++) {
        int j;
        for(j = 1 + i; j < N; j++) {
            bool hit = check(segments + i, segments + j, intersections + n_intersections);

            if(!hit)
                continue;

            n_intersections++;
            if(n_intersections == nalloc) {
                nalloc <<= 1;
                intersections = realloc(intersections, nalloc*sizeof(segment_t));
            }
        }
    }

    printf("%d total hits (including duplicates)\n", n_intersections);

    return 0;
    
    long np;
    long *p;
    primes(10000000, &p, &np);
    for(i = 0; i < n_intersections; i++) {
        long nx, dx, ny, dy;

        reduce(intersections[i].p0.a, intersections[i].p0.b, np, p, &nx, &dx);
        //printf("%ld/%ld => %ld/%ld\n", intersections[i].p0.a, intersections[i].p0.b, nx, dx);

        intersections[i].p0.a = nx;
        intersections[i].p0.b = dx;

        reduce(intersections[i].p1.a, intersections[i].p1.b, np, p, &ny, &dy);
        //printf("%ld/%ld => %ld/%ld\n", intersections[i].p1.a, intersections[i].p1.b, ny, dy);
        intersections[i].p1.a = ny;
        intersections[i].p1.b = dy;

        //printf("%ld/%ld\t%ld/%ld\n", nx, dx, ny, dy);
    }

    /*
    int n_unique = 0;
    for(i = 0; i < n_intersections; i++) {
        if(!(i % 100))
            printf("working on item %d\n", i);
        n_unique++;
        int j = 1 + i;
        while(j < n_intersections) {
            if(same_point(intersections + i, intersections + j)) {
                intersections[j] = intersections[--n_intersections];
            }
            j++;
        }
    }

    printf("%d unique hits\n", n_unique);
    */

    return 0;
}
