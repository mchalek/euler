#include <stdio.h>
#include <stdlib.h>

#define NUM_DIGITS 10
#define MAX_DIGIT_COUNT 3
#define MAX_COUNT 18
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))

// only need factorials of 0 through 3, but look out if we try to experiment
// with MAX_DIGIT_COUNT > 3!!
int factorials[] = {1, 1, 2, 6};

long count_permutations(int digits_used, int num_positions, int digit_counts[]) {
    // count the number of ways to fill num_positions with the objects described
    // by digit_counts.  This is the number of permutations, corrected for
    // exchanges of identical elements
    int i, j;

    long result = 1;
    for(i = 0; i < digits_used; i++) {
        for(j = 0; j < digit_counts[i]; j++) {
            result *= num_positions;
            num_positions--;
        }
        result /= factorials[digit_counts[i]];
    }

    return result;
}

long compute_variations(int digits_used, int digit_counts[]) {
    // count the ways to assemble the prescribed digits into a unique
    // number that does not start with 0.
    int i; // leading digit

    long result = 0;
    for(i = 1; i < digits_used; i++) {
        if(!digit_counts[i])
            continue;

        digit_counts[i] -= 1;

        result += count_permutations(digits_used, MAX_COUNT - 1, digit_counts);

        digit_counts[i] += 1;
    }

    return result;
}

long _build(int count, int digit, int digit_counts[]) {
    if(count == MAX_COUNT) {
        int i;
        for(i = 0; i < digit; i++) {
            printf("%d ", digit_counts[i]);
        }
        long result = compute_variations(digit, digit_counts);
        printf(" => %ld ways\n", result);

        return result;
    }

    long result = 0;
    // determine bounds on counts of this digit.  There are obvious upper limits,
    // but also there is a lower limit that applies when a certain number of
    // current digits is necessary to ensure completion.  For instance, suppose
    // count == 14 and digit == 8; We only have 8's and 9's left and we must
    // use at least one 8 (which works only if we use 3 9's)
    int min_count = MAX(0, MAX_COUNT - count - MAX_DIGIT_COUNT*(NUM_DIGITS-1-digit));
    int max_count = MIN(MAX_DIGIT_COUNT, MAX_COUNT-count);
    int i;
    for(i = min_count; i <= max_count; i++) {
        digit_counts[digit] = i;
        result += _build(count + i, digit + 1, digit_counts);
    }

    return result;
}

long build() {
    int digit_counts[10];
    return _build(0, 0, digit_counts);
}

int main()
{
    printf("result: %ld\n", build());

    return 0;
}
