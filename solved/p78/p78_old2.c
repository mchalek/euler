#include <stdio.h>
#include <stdlib.h>

/* OK it looks like I used some kind of dynamic programming
   approach to compute p(n), and now I'm doing a search.
   But the search is taking forever.  I should write down
   the recurrence relation and try to solve it analytically,
   or at least maybe reduce one of the steps here to remove a
   loop...  
   */


#define NMAX 100

#define BASE 1000
int main(void)
{
    int **c = malloc(NMAX*sizeof(int *));
    int i, j, n;

    c[0] = malloc(sizeof(int));
    c[0][0] = 1;
    i = 0;
    int *s = malloc(NMAX * sizeof(int));
    s[0] = 1;
    s[1] = 2;
    s[2] = 3;
    while(i < NMAX && c[i][i]) {
        i++;
        c[i] = malloc((i+1)*sizeof(int));
        c[i][0] = 1;
        for(j = 1; j < i; j++) {
            n = i + 1 - (j + 1);
            c[i][j] = (c[i][j-1] + ((j + 1 < n) ? 
                        (c[n-1][j]) : (s[n-1]))) % BASE;
            if(j + 1 == n) {
                s[n-1] = c[n-1][n-1];
                free(c[n-1]);
            }
        }
        c[i][i] = (c[i][i-1] + 1) % BASE;
        printf("p(%d) == %d\n", i + 1, c[i][i]);
    }
    if(c[i][i])
        printf("Search failed to find result for i < %d\n", NMAX);
    else
        printf("p(%d) == %d (mod %d)\n", i + 1, c[i][i], BASE);

    for(i = 0; i < NMAX; i++)
        printf("s[%d] == %d\n", i+1, s[i]);

    return 0;
}

