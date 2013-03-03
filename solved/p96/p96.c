#include <kmbits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint16_t *x[9];
} group_t;

typedef struct {
    uint16_t data[81];
    group_t boxes[9];
    group_t hlines[9];
    group_t vlines[9];
} puzz_t;

void link_puzz(puzz_t *puzz)
{
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            // horizontal lines
            puzz->hlines[i].x[j] = puzz->data + 9*i + j;

            // vertical lines
            puzz->vlines[i].x[j] = puzz->data + 9*j + i;

            // boxes
            // read in order of horizontal lines, computing
            // correct indices as you go
            puzz->boxes[3*(i/3) + (j/3)].x[3*(i%3) + (j%3)] = puzz->data + 9*i + j;
        }
    }
}

void load_puzz(char lines[][64], puzz_t *puzz)
{
    int i, j, load;

    // first load data
    for(i = 0; i < 9; i++) {
        load = atoi(lines[i]);
        for(j = 0; j < 9; j++) {
            int dig = load % 10;
            if(dig)
                puzz->data[i*9+8-j] = 1u << dig; // only one possible
            else
                puzz->data[i*9+8-j] = 0x3ff; // anything possible
            load /= 10;
        }
    }

    // next setup internal structures
    link_puzz(puzz);
}

void copy_puzz(puzz_t *dest, const puzz_t *src)
{
    *dest = *src;

    link_puzz(dest);
}

int reduce_group(group_t *group)
{
    int i, j;

    int changes;
    int tot_changes = 0;
    do {
        changes = 0;
        for(i = 0; i < 9; i++) {
            uint16_t bits = *(group->x[i]);
            int val = _trailz(bits);
            if(val) { 
                for(j = 0; j < 9; j++) {
                    if(i == j)
                        continue;
                    
                    uint16_t jbits = *(group->x[j]);
                    uint16_t jbits0 = jbits;
                    jbits &= ~(1u << val);

                    int pc = _popcnt(jbits >> 1);

                    if(!pc)
                        return -1;

                    if(pc == 1)
                        jbits &= ~1u;

                    *(group->x[j]) = jbits;
                    if(jbits != jbits0)
                        changes++;
                }
            }
        }
        tot_changes += changes;
    } while(changes);

    return tot_changes;
}

int reduce(puzz_t *puzz)
{
    int tot_changes = 0;
    int changes;
    int i, j;

    do {
        changes = 0;
        for(i = 0; i < 9; i++) {
            int result = reduce_group(puzz->boxes + i);

            if(result < 0)
                return -1;
            changes += result;

            result = reduce_group(puzz->hlines + i);
            if(result < 0)
                return -1;
            changes += result;

            result = reduce_group(puzz->vlines + i);
            if(result < 0)
                return -1;
            changes += result;
        }
        tot_changes += changes;
    } while(changes);

    return tot_changes;
}

void print_puzz(puzz_t *puzz)
{
    int i, j;

    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(puzz->data[9*i+j] & 1)
                printf(" 0 ");
            else
                printf(" %d ", 1+_trailz(puzz->data[9*i+j] >> 1));

            if(j == 2 || j == 5)
                printf(" | ");
        }
        printf("\n");

        if(i == 2 || i == 5) {
            printf("---------------------------------\n");
        }
    }
}

int count_complete(const puzz_t *puzz)
{
    int i;
    int complete = 81;
    for(i = 0; i < 81; i++) {
        if(puzz->data[i] & 1)
            complete--;
    }

    return complete;
}

int solve(puzz_t *puzz)
{
    int complete = 0;
    int i;
    int result = reduce(puzz);
    if(result < 0)
        return -1;

    complete = count_complete(puzz);

    if(complete == 81)
        return 0;

    for(i = 0; i < 81; i++) {
        if(puzz->data[i] & 1) {
            break;
        }
    }

    if(i == 81) {
        printf("FAIL\n");
        exit(0);
    }

    uint16_t bits = puzz->data[i] ^ 1;
    int n = _popcnt(bits);

    int j;
    for(j = 0; j < n; j++) {
        puzz_t test; 
        copy_puzz(&test, puzz);

        uint16_t bit = 1u << _trailz(bits);
        bits ^= bit;

        test.data[i] = bit;

        result = solve(&test);
        if(result > -1) {
            copy_puzz(puzz, &test);
            return 0;
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    if(argc == 1) {
        printf("syntax %s filename [print]\n", argv[0]);
        exit(0);
    }
    const char *filename = argv[1];
    int print = 1;
    if(argc > 2) {
        print = atoi(argv[2]);
    }
    //const char filename[] = "sudoku.txt";
    FILE *fp = fopen(filename, "r");
    char header[64];
    char lines[9][64];
    if(NULL == fp) {
        printf("could not open file: %s\n", filename);
        exit(0);
    }

    int linecount = 0;

    int sum = 0;
    while(NULL != fgets(header, sizeof(header), fp)) {
        // if we've read a line, it must be the group header line
        int i;
        linecount++;
        for(i = 0; i < 9; i++) {
            if(NULL == fgets(lines[i], sizeof(lines[i]), fp)) {
                printf("I/O Error on line %d\n", linecount);
                exit(0);
            }
            linecount++;
        }

        puzz_t puzz;
        load_puzz(lines, &puzz);

        if(print) {
            printf("%s\n", header);
            print_puzz(&puzz);
            printf("\n");
        }

        solve(&puzz);


        if(81 != count_complete(&puzz)) {
            printf("FAILED TO SOLVE\n");
        } else {
            if(print) {
                print_puzz(&puzz);
                printf("\n");
            }

            sum += (_trailz(puzz.data[0]) * 100) +
                   (_trailz(puzz.data[1]) * 10)  +
                   (_trailz(puzz.data[2]));
        }
    }

    printf("top-left sum: %d\n", sum);

    return 0;
}
