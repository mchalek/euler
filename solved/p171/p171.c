#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int factorials[11];
void init_factorials()
{
    int i;
    factorials[0] = 1;
    for(i = 1; i <= 10; i++) {
        factorials[i] = factorials[i-1]*i;
    }

    return;
}

void breakdown(int digits[], int *count, int *dsum)
{
    int dcounts[10];
    memset(dcounts, 0, sizeof(dcounts));
    int i;
    *dsum = 0;
    for(i = 0; i < 10; i++) {
        dcounts[digits[i]]++;
        *dsum += digits[i]*digits[i];
    }

    *count = factorials[10];
    for(i = 0; i < 10; i++)
        *count /= factorials[dcounts[i]];
}

inline int dsum(long num) {
    int ret = 0;
    while(num) {
        int dig = num % 10;
        ret += dig*dig;
        num /= 10;
    }

    return ret;
}

void traverse(int position, int last, int digits[], int nsq, int *squares, long *left_counts) {
    int i;
    if(position == 10) {
        int count, dsum;

        if(left_counts) {
            breakdown(digits, &count, &dsum);
            for(i = 0; i < nsq; i++) {
                int diff = squares[i] - dsum;
                if(diff >= 0)
                    left_counts[diff] += count;
            }
        } else {
            breakdown(digits, &count, &dsum);
            printf("digits:");
            for(i = 0; i < 10; i++) {
                printf(" %d", digits[i]);
            }

            printf(" -> %d [%d]\n", dsum, count);
        }

        return;
    }
    for(i = last; i < 10; i++) {
        digits[position] = i;
        traverse(position + 1, i, digits, nsq, squares, left_counts);
    }
}

int main(void) {
    int digits[10];
    init_factorials();

    // squares must be <= 81*20 == 1620 < 41^2
    int *squares = malloc(40*sizeof(int));
    long *left_counts = calloc(1601, sizeof(long));
    int i;
    for(i = 1; i < 41; i++) {
        squares[i-1] = i*i;
    }

    traverse(0, 0, digits, 40, squares, left_counts);
    long sum=0l;
    long rhs;
    for(rhs = 0; rhs < 10000000000l; rhs++) {
        sum += left_counts[dsum(rhs)] * rhs;
        sum %= 1000000000;

        if(sum % 1000000 == 0)
            printf("%ld %ld\n", rhs, sum);
    }
    printf("sum: %ld\n", sum);

    return 0;
}
