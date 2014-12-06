#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//: 3958113600
#define MAX_ENCODING 58806

long **encoding_counts_mod_11;
long **em11_lz;

int encode(int dcounts[])
{
    int i;
    int ret = 0;
    for(i = 0; i < 10; i++) {
        ret *= 3;
        ret += dcounts[i];
    }

    return ret;
}

void decode(int encoding, int dcounts[])
{
    memset(dcounts, 0, 10*sizeof(int));
    int i = 9;

    while(encoding) {
        dcounts[i] = encoding % 3;
        encoding /= 3;
        i--; 
    }
}

int complement(int encoding)
{
    int dcounts[10];
    decode(encoding, dcounts);

    int ccounts[10]; // complement counts
    memset(ccounts, 0, sizeof(ccounts));
    int i;
    for(i = 0; i < 10; i++)
        ccounts[i] = 2 - dcounts[i];

    return encode(ccounts);
}

long count(long num, int depth, int dcounts[]) {
    if(depth == 10) {
        long lead = num / 1000000000l;
        int e = encode(dcounts);
        long mod11 = num % 11;

        if(lead)
            encoding_counts_mod_11[mod11][e]++;
        else
            em11_lz[mod11][e]++;
        return 1;
    }

    long ret = 0;
    int dig;
    for(dig = 0; dig < 10; dig++) {
        if(dcounts[dig] == 2)
            continue;

        dcounts[dig]++;
        ret += count(num * 10 + dig, 1 + depth, dcounts);
        dcounts[dig]--;
    }

    return ret;
}

int isvalid(int encoding)
{
    int ndig[10];
    decode(encoding, ndig);

    int i;
    int sum = 0;
    for(i = 0; i < 10; i++) {
        if(ndig[i] > 2)
            return 0;

        sum += ndig[i];
    }

    return sum == 10;
}

int main()
{
    encoding_counts_mod_11 = malloc(11*sizeof(long *));
    em11_lz = malloc(11*sizeof(long *));
    int i;
    for(i = 0; i < 11; i++) {
        encoding_counts_mod_11[i] = calloc(1 + MAX_ENCODING, sizeof(long));
        em11_lz[i] = calloc(1 + MAX_ENCODING, sizeof(long));
    }

    int dcounts[10];
    memset(dcounts, 0, sizeof(dcounts));
    long c = count(0, 0, dcounts);

    printf("count: %ld\n", c);

    long z = 10000000000l % 11;

    long result = 0;
    for(i = 0; i < 11; i++) {
        long lhs_mod_11 = (i * z) % 11;
        long mod_complement = (11 - lhs_mod_11) % 11;

        int j;
        for(j = 0; j <= MAX_ENCODING; j++) {
            if(!isvalid(j))
                continue;

            int jj[10], kk[10];
            decode(j, jj);
            int comp = complement(j);
            decode(comp, kk);

            int k;
            for(k = 0; k < 10; k++) {
                fprintf(stderr, "%d ", jj[k]);
            }
            fprintf(stderr, "| ");
            for(k = 0; k < 10; k++) {
                fprintf(stderr, "%d ", kk[k]);
            }
            fprintf(stderr, "\n");
            fprintf(stderr, "(%d, %d) * (%ld, %d)\n", i, j, mod_complement, comp);
            fprintf(stderr, "%ld lhs, %ld rhs\n", encoding_counts_mod_11[i][j], encoding_counts_mod_11[mod_complement][comp]);

            result += encoding_counts_mod_11[i][j] *
                (encoding_counts_mod_11[mod_complement][comp] + em11_lz[mod_complement][comp]);
        }
    }

    printf("result? %ld\n", result);

    return 0;
}
