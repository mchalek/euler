#include <stdio.h>

#define MAXX 50
#define MAXY 50

//#define MAXX 2
//#define MAXY 2

#define ABS(x) (((x) < 0) ? -(x) : x)

int main()
{
    int x1, y1, x2, y2;

    long count = 0;

    for(x1 = 0; x1 <= MAXX; x1++) {
        for(y1 = 0; y1 <= MAXY; y1++) {
            int a1 = x1*x1 + y1*y1;
            if(!a1)
                continue;
            for(x2 = 0; x2 <= MAXX; x2++) {
                for(y2 = 0; y2 <= MAXY; y2++) {
                    int a2 = x2*x2 + y2*y2;

                    if(!a2)
                        continue;

                    int dx = ABS(x1-x2);
                    int dy = ABS(y1-y2);
                    int a3 = dx*dx + dy*dy;
                    
                    if(!a3)
                        continue;

                    if(a1 + a2 == a3 || a1 + a3 == a2 || a2 + a3 == a1) {
                        printf("(%d, %d) -> (%d, %d)\n", x1, y1, x2, y2);
                        count++;
                    }
                }
            }
        }
    }

    // note that the above double-counts, so we must divide by 2
    printf("count: %ld\n", count / 2);
}
