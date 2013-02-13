#include <stdio.h>
int main(void)
{
    int a, b, c, d, e, f, g, h, i, j;
    int used = 0;
    long sum = 0l;
    for(a = 0; a < 10; a++) {
        used = 1 << a;
    for(b = 0; b < 10; b++) {
        if(1 & (used >> b))
            continue;
        used ^= (1 << b);
    for(c = 0; c < 10; c++) {
        if(1 & (used >> c))
            continue;
        used ^= (1 << c);
    for(d = 0; d < 10; d++) {
        if(1 & (used >> d))
            continue;
        used ^= (1 << d);
    for(e = 0; e < 10; e++) {
        if(1 & (used >> e))
            continue;
        used ^= (1 << e);
    for(f = 0; f < 10; f++) {
        if(1 & (used >> f))
            continue;
        used ^= (1 << f);
    for(g = 0; g < 10; g++) {
        if(1 & (used >> g))
            continue;
        used ^= (1 << g);
    for(h = 0; h < 10; h++) {
        if(1 & (used >> h))
            continue;
        used ^= (1 << h);
    for(i = 0; i < 10; i++) {
        if(1 & (used >> i))
            continue;
        used ^= (1 << i);
        for(j = 0; j < 10; j++) {
        if(1 & (used >> j))
            continue;
        long x = j + 10l*i + 100l * h + 1000l * g + 10000l * f + 100000l * e + 
                 1000000l * d + 10000000l * c + 100000000l * b + 1000000000l * a;
        //printf("%010ld\n", x);

        if((b*100+c*10+d) % 2) {
            continue;
        }
        if((c*100+d*10+e) % 3)
            continue;
        if((d*100+e*10+f) % 5)
            continue;
        if((e*100+f*10+g) % 7)
            continue;
        if((f*100+g*10+h) % 11)
            continue;
        if((g*100+h*10+i) % 13)
            continue;
        if((h*100+i*10+j) % 17)
            continue;
        
        x = j + 10l*i + 100l * h + 1000l * g + 10000l * f + 100000l * e + 
                 1000000l * d + 10000000l * c + 100000000l * b + 1000000000l * a;
        printf("%ld\n", x);
        sum += x;

        }
        used ^= (1 << i);
    }
        used ^= (1 << h);
    }
        used ^= (1 << g);
    }
        used ^= (1 << f);
    }
        used ^= (1 << e);
    }
        used ^= (1 << d);
    }
        used ^= (1 << c);
    }
        used ^= (1 << b);
    }
    }
printf("sum is %ld\n", sum);
}
