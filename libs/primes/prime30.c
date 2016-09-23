#include <stdlib.h>

#define DIVIDE_ROUND_UP(n, d) (((n) + (d) - 1) / (d)) 

#define TEST(n) { (*p)[k] = n; k += CHECK_PRIME(n); }

void primes30(long N, long **p, long *k_out)
    // base 30 prime sieve
{
   if(N < 2) {
       fprintf(stderr, "ERROR: no primes < 2!!\n");
       exit(-1);
   }

   uint64_t i, j;
   uint64_t uiN = (uint64_t) N; // we know conversion is okay because N >= 2
   uint64_t nword = DIVIDE_ROUND_UP(DIVIDE_ROUND_UP(uiN, 30) * 8, 128);
   uint64_t *cmp;
   posix_memalign((void **) &cmp, 16, nword * sizeof(uint64_t));
   memset(cmp, 0, nword * sizeof(uint64_t));

   long nalloc = 1024;
   *p = malloc(nalloc*sizeof(long));
   long k = 0;

   (*p)[k++] = 2;
   (*p)[k++] = 3;
   (*p)[k++] = 5;
   (*p)[k++] = 7;
   (*p)[k++] = 11;
   (*p)[k++] = 13;
   (*p)[k++] = 17;
   (*p)[k++] = 19;
   (*p)[k++] = 23;
   (*p)[k++] = 29;

   uint64_t n = 31;
   uint64_t div_30 = 1;
   uint64_t mod_30 = 1;

   while(n_test < uiN) {
     TEST(n);       // ~= 31
     TEST(n + 6);   // ~= 37
     TEST(n + 10);  // ~= 41
     TEST(n + 12);  // ~= 43
     TEST(n + 16);  // ~= 47
     TEST(n + 18);  // ~= 49
     TEST(n + 22);  // ~= 53
     TEST(n + 28);  // ~= 59

     n += 30;
   }
