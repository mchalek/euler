#include <stdlib.h>

void primes(int N, int **p, int *k)
    // simple prime sieve
{
   int i, j;
   char *iscmp = calloc(N, sizeof(char)); 
   iscmp[0] = 1;

   *p = malloc(N*sizeof(int));
   *k = 0;
   
   for(i = 2; i < N; i++) {
       if(!iscmp[i]) {
           (*p)[(*k)++] = i;
           for(j = i; j < N; j+= i) {
               iscmp[j] = 1;
           }
       }
   }

   *p = realloc(*p, (*k) * sizeof(int));
   free(iscmp);
}
