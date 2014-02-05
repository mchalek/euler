#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef union halfgrid {
    struct explicit {
        int8_t colsums[4];
        int8_t diagsums[4];
    } explicit;

    uint64_t together;
} hgrid_t;

typedef struct row {
    int8_t entries[4];
} row_t;

typedef struct grid_count {
    uint64_t grid;
    long count;
} grid_count_t;

int8_t sum4(int8_t entries[4]) {
    return entries[0] + entries[1] + entries[2] + entries[3];
}

long exhaust_rows(int8_t entries[4], long depth, row_t **out, long num_row[], long num_alloc[]) {
    if(depth == 4) {
        int8_t sum = sum4(entries);

        if(num_row[sum] == num_alloc[sum]) {
            num_alloc[sum] += 1000;
            out[sum] = realloc(out[sum], num_alloc[sum] * sizeof(row_t));
        }
        row_t row;
        memcpy(row.entries, entries, 4*sizeof(int8_t));
        memcpy(out[sum] + num_row[sum], &row, sizeof(row));
        num_row[sum]++;

        return 1l;
    }

    long total = 0l;
    int i;
    for(i = 0; i < 10; i++) {
        entries[depth] = i;
        total += exhaust_rows(entries, depth+1, out, num_row, num_alloc);
    }

    return total;
}

uint64_t lower_mask, upper_mask;

void set_masks() {
    hgrid_t lower, upper;
    memset(&lower, 0, sizeof(lower));
    memset(&upper, 0, sizeof(upper));

    // flag the ones we don't care about, then invert
    lower.explicit.diagsums[0] = 0xff;
    lower.explicit.diagsums[3] = 0xff;

    upper.explicit.diagsums[1] = 0xff;
    upper.explicit.diagsums[2] = 0xff;

    lower_mask = ~lower.together;
    upper_mask = ~upper.together;
}

int grid_cmp_lower(const void *va, const void *vb) {
    uint64_t a = *((uint64_t *) va) & lower_mask;
    uint64_t b = *((uint64_t *) vb) & lower_mask;

    return (a < b) ? -1 : (1 - (a == b));
}

long uniq_dc(uint64_t *hgrids, long ngrid, grid_count_t *unique) {
    if(!ngrid)
        return 0;

    long ucount = 0; // unique count

    uint64_t *stop = hgrids + ngrid;
    grid_count_t gc;
    gc.grid = *hgrids;
    gc.count = 1;
    for(hgrids++; hgrids < stop; hgrids++) {
        if(!grid_cmp_lower(hgrids, &gc.grid)) {
            gc.count++;
        } else {
            unique[ucount++] = gc;
            gc.grid = *hgrids;
            gc.count = 1;
        }
    }
    unique[ucount++] = gc;

    return ucount;
}

int grid_count_cmp(const void *va, const void *vb) {
    // for checking whether a lower-half matches a target lower-half
    grid_count_t *a = (grid_count_t *) va;
    grid_count_t *b = (grid_count_t *) vb;

    return grid_cmp_lower(&(a->grid), &(b->grid));
}

void compute_target(uint64_t grid, int8_t total, uint64_t *out) {
    hgrid_t hgrid;
    hgrid.together = grid;

    hgrid_t hout;

    int8_t *columns = hgrid.explicit.colsums;
    int8_t *diag = hgrid.explicit.diagsums;

    hout.explicit.colsums[0] = total-columns[0];
    hout.explicit.colsums[1] = total-columns[1];
    hout.explicit.colsums[2] = total-columns[2];
    hout.explicit.colsums[3] = total-columns[3];

    // ARGH! comparator isn't right, shouldn't care about two of the colsums
    // exhaust top  half and find bottom half => don't care about diag[1] and diag[3]
    // also use comparator in uniq_dc
    hout.explicit.diagsums[1] = total-diag[3];
    hout.explicit.diagsums[2] = total-diag[0];

    *out = hout.together;
}

long match_em_up(uint64_t *upper, long n_upper, grid_count_t *lower, long n_lower, int8_t total) {
    long ret = 0l;

    uint64_t *stop = upper + n_upper;
    for(; upper < stop; upper++) {
        uint64_t target;
        compute_target(*upper, total, &target);
        
        grid_count_t *hit = bsearch(&target, lower, n_lower, sizeof(grid_count_t), grid_count_cmp);

        if(!hit) 
            continue;

        ret += hit->count;
    }

    return ret;
}

int main(void) {
    set_masks();

    row_t **rows = malloc(37*sizeof(row_t *));
    long *num_row = calloc(37, sizeof(long));
    long *num_alloc = calloc(37, sizeof(long));
    int8_t i;
    for(i = 0; i < 37; i++)
        rows[i] = NULL;

    int8_t tmp[4];
    // first create all valid rows
    exhaust_rows(tmp, 0, rows, num_row, num_alloc);

    long result = 0l;

    for(i = 0; i < 37; i++) {
        long ngrid = 0l;
        uint64_t *hgrids = malloc(num_row[i]*num_row[i]*sizeof(hgrid_t));
        long j, k;
        for(j = 0; j < num_row[i]; j++) {
            int8_t *row0 = rows[i][j].entries;
            hgrid_t hgrid;
            for(k = 0; k < num_row[i]; k++) {
                int8_t *row1 = rows[i][k].entries;

                hgrid.explicit.colsums[0] = row0[0] + row1[0];
                hgrid.explicit.colsums[1] = row0[1] + row1[1];
                hgrid.explicit.colsums[2] = row0[2] + row1[2];
                hgrid.explicit.colsums[3] = row0[3] + row1[3];

                hgrid.explicit.diagsums[0] = row0[0] + row1[1];
                hgrid.explicit.diagsums[1] = row0[1] + row1[0];
                hgrid.explicit.diagsums[2] = row0[2] + row1[3];
                hgrid.explicit.diagsums[3] = row0[3] + row1[2];

                hgrids[ngrid++] = hgrid.together;
            }
        }

        qsort(hgrids, ngrid, sizeof(uint64_t), grid_cmp_lower);

        grid_count_t *grids_with_counts = malloc(ngrid*sizeof(grid_count_t));
        long n_lower = uniq_dc(hgrids, ngrid, grids_with_counts); // # valid lower half-grids

        result += match_em_up(hgrids, ngrid, grids_with_counts, n_lower, i);

        free(grids_with_counts);
    }

    printf("counted: %ld\n", result);

    return 0;
}
