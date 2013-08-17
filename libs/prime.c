#include <stdlib.h>

int primes(unsigned int N, unsigned int **p, unsigned int *k)
    // simple prime sieve
{
   int i, j;
   unsigned char *iscmp = calloc(N, sizeof(char)); 
   iscmp[0] = 1;

   *p = malloc(N*sizeof(unsigned int));
   *k = 0;
   
   for(i = 2; i < N; i++) {
       if(!iscmp[i]) {
           (*p)[(*k)++] = i;
           for(j = i; j < N; j+= i) {
               iscmp[j] = 1;
           }
       }
   }

   *p = realloc(*p, (*k) * sizeof(unsigned int));
   free(iscmp);
}
