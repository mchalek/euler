#include <stdio.h>

int dsum(int x)
{
    int ret = 0;
    while(x) {
        ret += x % 10;
        x /= 10;
    }

    return ret;
}

int main(void)
{
    int i, j = 0;

    for(i = 23; i < 100000; i += 23)
        if(dsum(i) == 23) {
            printf("i == %d; Delta == %d; i / 11 == %d\n", i, i - j, i / 11);
            j = i;
        }

    return 0;
}
