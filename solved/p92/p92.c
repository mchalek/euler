#include <stdio.h>

static inline int find(int a)
{
    while(a != 89 && a != 1) {
        int b = a;
        a = 0;

        while(b) {
            a += (b % 10)*(b % 10);
            b /= 10;
        }
    }

    return a;
}

int main(void)
{
    int i;
    int n = 0;

    for(i = 2; i < 10000000; i++) {
        n += find(i) == 89;
    }
    printf("%d\n", n);
}
