#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOPDEPTH 13

#define RAD(deg) ((deg / 180.0)*M_PI)

typedef struct {
double x;
double y;
int angle;
int count;
} list_t;

// plan: exhaust all 35-step possibilities, match up and count

static inline int cmp(list_t *a, list_t *b)
{
    if(a->x == b->x && a->y == b->y && a->angle == b->angle)
        return 0;

    if(a->x > b->x) {
        return 1;
    } else if(a->x < b->x) {
        return -1;
    } else {
        if(a->y > b->y) {
            return 1;
        } else if(a->y < b->y) {
            return -1;
        } else {
            if(a->angle > b->angle) {
                return 1;
            } else {
                return -1;
            }
        }
    }

    return 0;
}

void insert(double x, double y, int angle, long *nalloc, long *npts, list_t **pl)
{
    list_t new = {x, y, angle, 0};
    list_t *l = *pl;
    int a, b, c;
    
    a = 0;
    b = *npts;
    c = (a + b) / 2;

    int d = 0;

    while(b > a) {
        d = cmp(l + c, &new);
        if(!d) {
            l[c].count++;
            return;
        }

        if(d == 1) {
            b = c;
        } else {
            a = c+1;
        }
    }

    if(*nalloc == *npts) {
        *nalloc *= 2;
        *pl = realloc(*pl, *nalloc * sizeof(list_t));
        l = *pl;
    }

    d = cmp(l + a, &new);

    if(d == 1) {
        memmove(l + a + 1, l + a, (*npts - a)*sizeof(list_t));
    } else {
        memmove(l + a + 2, l + a + 1, (*npts - a - 1)*sizeof(list_t));
    }
    l[a] = new;
}

void exh(int depth, double x, double y, int angle, double delta_table[5][2][2], long *nalloc, long *npts, list_t **l)
{
    if(depth == STOPDEPTH) {
        insert(x, y, angle, nalloc, npts, l);
        return;
    }
    double new_x;
    double new_y;
    int new_angle;

    new_angle = (angle + 1) % 5;
    new_x = x + delta_table[angle][1][0];
    new_y = y + delta_table[angle][1][1];

    exh(depth+1, new_x, new_y, new_angle, delta_table, nalloc, npts, l);

    new_angle = (angle + 4) % 5;
    new_x = x + delta_table[angle][0][0];
    new_y = y + delta_table[angle][0][1];

    exh(depth+1, new_x, new_y, new_angle, delta_table, nalloc, npts, l);

    return;
}

int main(void)
{
    unsigned long i;
    long nalloc = 100000;
    long npts = 0;
    list_t *l = malloc(nalloc*sizeof(list_t));

    double delta_table[5][5][2];
    int angle; 
    double x, y;

    for(angle = 0; angle < 10; angle++) {
        delta_table[angle % 5][angle / 2][0] = 0.0;
        delta_table[angle % 5][angle / 2][1] = 0.0;
    }

    delta_table[0][1][0] = cos(RAD(72.0))-1.0;
    delta_table[0][1][1] = sin(RAD(72.0));
    delta_table[0][0][0] = -delta_table[0][1][0];
    delta_table[0][0][1] = delta_table[0][1][1];

    double checkx1, checky1, checkx0, checky0;

    checkx1 = delta_table[0][1][0];
    checkx0 = delta_table[0][0][0];
    checky1 = delta_table[0][1][1];
    checky0 = delta_table[0][0][1];

    printf("check x1 %g x0 %g y1 %g y0 %g\n", checkx1, checkx0, checky1, checky0);

    for(angle = 1; angle < 5; angle++) {
        delta_table[angle][1][0] =  cos(RAD(72.0))*delta_table[angle-1][1][0] - sin(RAD(72.0))*delta_table[angle-1][1][1];
        delta_table[angle][1][1] = sin(RAD(72.0))*delta_table[angle-1][1][0] + cos(RAD(72.0))*delta_table[angle-1][1][1];

        delta_table[angle][0][0] =  cos(RAD(72.0))*delta_table[angle-1][0][0] - sin(RAD(72.0))*delta_table[angle-1][0][1];
        delta_table[angle][0][1] = sin(RAD(72.0))*delta_table[angle-1][0][0] + cos(RAD(72.0))*delta_table[angle-1][0][1];

        checkx1 = delta_table[angle][1][0];
        checkx0 = delta_table[angle][0][0];
        checky1 = delta_table[angle][1][1];
        checky0 = delta_table[angle][0][1];

        printf("check x1 %g x0 %g y1 %g y0 %g\n", checkx1, checkx0, checky1, checky0);
    }

    printf("check x1 %g x0 %g y1 %g y0 %g\n", checkx1, checkx0, checky1, checky0);

    return 0;
}
