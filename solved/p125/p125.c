#include <stdio.h>
#include <stdlib.h>

#define MAX 100000000
//#define MAX 1000

int ispal(int x)
{
    int n = x;
    int y = 0;
    while(n) {
        int digit = n % 10;
        n /= 10;

        y *= 10;
        y += digit;
    }

    return y == x;
}

int main()
{
    int max_n = 1;
    while(max_n * max_n < MAX)
        max_n++;

    printf("max_n is %d\n", max_n);

    int *S = malloc((max_n + 1) * sizeof(int));

    int i;
    for(i = 1; i <= max_n; i++)
        S[i-1] = i*i;

    int left = 0, right = 0, sum = 0;

    long result = 0;

    // prevent reporting duplicates
    char *hits = calloc(1 + MAX, sizeof(char));
    for(left = 0; left < max_n-1; left++) {
        sum = S[left];

        if(sum + S[left+1] > MAX)
            break;
        
        right = left+1;
        while(sum + S[right] < MAX) {
            sum += S[right++];
            if(hits[sum])
                continue;

            if(ispal(sum)) {
                printf("sum[%d, %d] == %d is a palindrome!\n",
                        left+1, right, sum);
                result += sum;
                hits[sum] = 1;
            }
        }
    }

    printf("result: %ld\n", result);

    return 0;
}
