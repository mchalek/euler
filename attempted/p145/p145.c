#include <stdio.h>
#include <stdlib.h>

inline int isrev(long a)
{
    long ret = a;
    long ra = 0;
    while(a) {
        ra *= 10;
        ra += a % 10;
        a /= 10;
    }

    long revsum = ret + ra;

    while(revsum) {
        if(!(revsum % 2))
            return 0;
        revsum /= 10;
    }
    return 1;
}

int main(int argc, char **argv)
{
    long x;
    if(argc != 2) {
        printf("SYNTAX: %s maxx\n", argv[0]);
        exit(0);
    }
    long maxx = strtol(argv[1], NULL, 10);
    long sum = 0;

    for(x = 12; x < maxx; x ++) {
        if(0 == (x % 10))
            continue;
        if(isrev(x))
            sum ++;
    }
    printf("num: %ld\n", sum);
}
