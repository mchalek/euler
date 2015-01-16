#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void *va, const void *vb)
{
    long a = *((long *) va);
    long b = *((long *) vb);

    return (a == b) ? 0 : (1 - 2*(a < b));
}

int main()
{
    const long max_p = 1000000000l;

    const long max_a = (max_p + 1l) / 3l;
    printf("max a is: %ld\n", max_a);

    const long max_sqrt = (long) ceil(sqrt(3*max_a*max_a + 2*max_a + 1));
    printf("max sqrt is: %ld\n", max_sqrt);
    fflush(stdout);

    long *squares = calloc(1 + max_sqrt, sizeof(long));

    long i;
    long num_squares = 0;
    for(i = 0; i <= max_sqrt; i += 2)
        squares[num_squares++] = i*i;

    squares = realloc(squares, num_squares*sizeof(long));

    printf("Computed squares.\n");

    long a;
    long psum = 0;
    for(a = 3; a <= max_a; a += 2) {
        long test0 = 3*a*a + 2*a - 1;
        if(bsearch(&test0, squares, num_squares, sizeof(long), cmp)) {
            printf("hit on %ld x %ld x %ld!\n", a, a, a-1);
            psum += 3*a - 1;
        }

        long test1 = 3*a*a - 2*a - 1;
        if(bsearch(&test1, squares, 1 + max_sqrt, sizeof(long), cmp)) {
            printf("hit on %ld x %ld x %ld!\n", a, a, a+1);
            psum += 3*a + 1;
        }
    }

    printf("sum of perimeters: %ld\n", psum);

    return 0;
}
