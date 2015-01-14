#include <stdio.h>

#define target 2000000

long count(int nrow, int ncol)
{
    long total = 0;

    int l, w;
    for(l = 1; l <= nrow; l++) {
        long nl = nrow - l + 1;
        for(w = 1; w <= ncol; w++) {
            // how many ways to fit a l x w rectangle into the nrow x ncol bigger rectangle?
            long nr = ncol - w + 1;

            //printf("%d x %d: %ld\n", l, w, nl * nr);
            
            total += nl * nr;
        }
    }

    return total;
}

#define ABS(x) (((x) < 0) ? -(x) : (x))

int main()
{
    int x, y;
    long delta;
    long min = count(100, 100);
    long min_delta = ABS(min-target);
    long min_area = 10000;

    for(x = 1; x < 100; x++) {
        for(y = 1; y <= x; y++) {
            long num = count(x, y);
            long delta = ABS(num - target);

            if(delta < min_delta) {
                min_delta = delta;
                min_area = x*y;
                min = num;
            }
        }
    }

    printf("area of closest rectangle: %ld\n", min_area);
    printf("closest count: %ld\n", min);


    return 0;
}
