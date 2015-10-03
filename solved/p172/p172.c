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

long _build(int count, int digit, int digit_counts[]) {
    // Exhaust all possible digit counts, and add up the number of unique ways
    // to arrange each set of counts.  Note that we allow leading 0's here, 
    // so we must correct the total count in the calling method.
    if(count == MAX_COUNT)
        return count_permutations(digit, MAX_COUNT, digit_counts);

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
    long with_leading_zeros = _build(0, 0, digit_counts);
    // correct counts: exactly 90% do not start with 0
    return with_leading_zeros / 10 * 9;
}

int main()
{
    printf("result: %ld\n", build());

    return 0;
}
