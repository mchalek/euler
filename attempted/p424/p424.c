#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

typedef enum {heq=1, veq=2, open=4, gray=8, filled=16} box_type_t;
typedef struct {
    box_type_t type;
    int fill[10];
    int veq_rhs[10];
    int heq_rhs[10];
} box_t;

typedef struct {
    int neq;
    int nvar;
    int nulldim;
    int num_rhsnull;
    int *lhs;
    int *rhs;
    int *rhsnull;
} eqn_t;

void create_eqns(int dim, box_t *puzz, eqn_t *eqn)
{
    int nbox = dim*dim;
    int var_ind[nbox];
    int i;
    eqn->neq = 0;
    eqn->nvar = 0;
    // first loop through and determine equation size, and assign
    // variable indices
    for(i = 0; i < nbox; i++) {
        if(puzz[i].type & veq) {
            eqn->neq++;
        }
        if(puzz[i].type & heq) {
            eqn->neq++;
        }
        if(puzz[i].type == open) {
            var_ind[i] = eqn->nvar++;
        }
    }

    printf("%d eqns, %d vars\n", eqn->neq, eqn->nvar);

    eqn->lhs = calloc(eqn->neq*eqn->nvar, sizeof(int));
    eqn->rhs = calloc(eqn->neq*10, sizeof(int));
    int ix = 0;

    for(i = 0; i < nbox; i++) {
        if(puzz[i].type & heq) {
            int *rhs = eqn->rhs + ix*10;
            int *lhs = eqn->lhs + ix*eqn->nvar;
            int j, k;
            memcpy(rhs, puzz[i].heq_rhs, 10*sizeof(int));
            for(j = i+1; (j % dim) != 0; j++) {
                if(puzz[j].type & (veq|heq|gray))
                    break;
                if(puzz[j].type & open) {
                    lhs[var_ind[j]] += 1;
                }
                if(puzz[j].type & filled) {
                   for(k = 0; k < 10; k++)
                       rhs[k] -= puzz[j].fill[k];
                }
            }

            printf("h%02d ", i);
            for(j = 0; j < eqn->nvar; j++)
                printf("%d ", lhs[j]);
            printf("/ ");
            for(j = 0; j < 10; j++)
                printf("%d ", rhs[j]);
            printf("\n");
            fflush(stdout);

            ix++;
        }
        if(puzz[i].type & veq) {
            int *rhs = eqn->rhs + ix*10;
            int *lhs = eqn->lhs + ix*eqn->nvar;
            int j, k;
            memcpy(rhs, puzz[i].veq_rhs, 10*sizeof(int));
            for(j = i+dim; j < nbox; j += dim) {
                if(puzz[j].type & (veq|heq|gray))
                    break;
                if(puzz[j].type & open) {
                    lhs[var_ind[j]] += 1;
                }
                if(puzz[j].type & filled) {
                   for(k = 0; k < 10; k++)
                       rhs[k] -= puzz[j].fill[k];
                }
            }

            printf("v%02d ", i);
            for(j = 0; j < eqn->nvar; j++)
                printf("%d ", lhs[j]);
            printf("/ ");
            for(j = 0; j < 10; j++)
                printf("%d ", rhs[j]);
            printf("\n");
            fflush(stdout);

            ix++;
        }
    }
}

void reduce_eqns(eqn_t *eqn) {
    // reduce LHS to upper-triangular
    int nvar = eqn->nvar;
    int neq = eqn->neq;

    int *tmp_row = malloc(MAX(nvar, 10)*sizeof(int));

    int i;
    int targ = 0;
    for(i = 0; i < neq; i++) {
        int j;
        // find an element with nonzero i index
        int hit = 0;
        for(j = i; j < neq; j++) {
            int *lhs = eqn->lhs + j*nvar;
            if(lhs[i] != 0) {
                hit = 1;
                break;
            }
        }
        if(hit) {
            // swap rows
            // first lhs
            memcpy(tmp_row, eqn->lhs + j*nvar, nvar*sizeof(int));
            memcpy(eqn->lhs + j*nvar, eqn->lhs + targ*nvar, nvar*sizeof(int));
            memcpy(eqn->lhs + targ*nvar, tmp_row, nvar*sizeof(int));

            // now rhs
            memcpy(tmp_row, eqn->rhs + j*10, 10*sizeof(int));
            memcpy(eqn->rhs + j*10, eqn->rhs + targ*10, 10*sizeof(int));
            memcpy(eqn->rhs + targ*10, tmp_row, 10*sizeof(int));
            
            // now wipeout column
            for(j = targ+1; j < neq; j++) {
                int *eq = eqn->lhs + j*nvar;
                if(eq[i] != 0) {
                    int k;
                    int scalej = eqn->lhs[targ*nvar + i];
                    int scalei = eqn->lhs[j*nvar + i];

                    for(k = 0; k < nvar; k++) {
                        eqn->lhs[j*nvar + k] *= scalej;
                        eqn->lhs[j*nvar + k] -= scalei*eqn->lhs[targ*nvar + k];
                    }

                    for(k = 0; k < 10; k++) {
                        eqn->rhs[j*10 + k] *= scalej;
                        eqn->rhs[j*10 + k] -= scalei*eqn->rhs[targ*10 + k];
                    }
                }
            }
            targ++;
        }
    }

    // now it is upper-triangular; just need to separate out nullspace
    eqn->num_rhsnull = 0;
    for(i = 0; i < neq; i++) {
        int null = 1;
        int j;
        for(j = 0; j < nvar; j++)
            null &= eqn->lhs[i*nvar + j] == 0;
        eqn->num_rhsnull += null;
    }

    if(eqn->num_rhsnull) {
        eqn->rhsnull = malloc(eqn->num_rhsnull*10);
        int ix = 0;
        for(i = 0; i < neq; i++) {
            int null = 1;
            int j;
            for(j = 0; j < nvar; j++)
                null &= eqn->lhs[i*nvar + j] == 0;
            if(null) {
                memcpy(eqn->rhsnull + ix*10, eqn->rhs + i*10, 10*sizeof(int));
                ix++;
            }
        }
    }
    eqn->nulldim = eqn->num_rhsnull + ((nvar > neq) ? (nvar-neq) : 0);
    eqn->neq -= eqn->num_rhsnull;
    // finally permute columns so that free variables always come last
    // we don't have to recover actual values for solution, so we don't 
    // bother keeping track of the permutation
    
    neq = eqn->neq;
    for(i = 0; i < neq; i++) {
        if(eqn->lhs[i*nvar + i] == 0) {
            int j;
            int hit = 0;
            for(j = i+1; j < nvar; j++) {
                if(eqn->lhs[i*nvar + j] != 0) {
                    hit = 1;
                    break;
                }
            }
            if(hit) {
                // swap columns i and j on LHS
                int k;
                int tmp;
                for(k = 0; k < neq; k++) {
                    tmp = eqn->lhs[k*nvar + i];
                    eqn->lhs[k*nvar + i] = eqn->lhs[k*nvar + j];
                    eqn->lhs[k*nvar + j] = tmp;
                }
            }
        }
    }
    
    // make sure diagonal values are positive
    for(i = 0; i < neq; i++) {
        int val = eqn->lhs[i*nvar + i];
        if(val < 0) {
            int j;
            for(j = 0; j < nvar; j++)
                eqn->lhs[i*nvar + j] *= -1;

            for(j = 0; j < 10; j++)
                eqn->rhs[i*10+j] *= -1;
        }

    }

    free(tmp_row);

    // print out resulting equations
    for(i = 0; i < neq; i++) {
        int *lhs = eqn->lhs + i*nvar;
        int *rhs = eqn->rhs + i*10;

        int j;
        for(j = 0; j < nvar; j++)
            printf("% 3d ", lhs[j]);
        printf("/ ");
        for(j = 0; j < 10; j++)
            printf("% 3d ", rhs[j]);
        printf("\n");
    }

    printf("RHS constraints: \n");
    for(i = 0; i < eqn->num_rhsnull; i++) {
        int j;
        printf("\t");
        for(j = 0; j < 10; j++)
            printf("% 3d ", eqn->rhsnull[i*10+j]);
        printf("\n");
    }

    printf("%d free variables\n", eqn->nvar-eqn->nulldim);
}

void fill_eq(char eq[], box_t *box) {
    int *coeffs;
    if(eq[0] == 'v') {
        box->type |= veq;
        coeffs = box->veq_rhs;
    } else {
        box->type |= heq;
        coeffs = box->heq_rhs;
    }

    eq++;

    int mul = 1;
    int j = strlen(eq)-1;
    while(j >= 0) {
        coeffs[eq[j] - 'A'] += mul;
        mul *= 10;
        j--;
    }
}

int idot(int N, int a[], int b[]) {
    int k;
    int ret = 0;
    for(k = 0; k < N; k++)
        ret += a[k]*b[k];
    return ret;
}


int test_eqns(int AJ[10], eqn_t *eqns) {
    int i;
    for(i = 0; i < eqns->num_rhsnull; i++) {
        if(idot(10, eqns->rhsnull + i*10, AJ))
            return 0;
    }
    return 1;
}

int checker2(int AJ[10], eqn_t *eqns, int x[], int depth) {
    if(depth == eqns->nulldim) {
        int i;

        int hits[eqns->neq];
        int rhsz[eqns->neq];
        int lhsz[eqns->neq];
        
        for(i = eqns->neq-1; i >= 0; i--) {
            int rhs = idot(10, eqns->rhs + 10*i, AJ);
            int lower_dot = idot(eqns->nvar - i - 1, x + i + 1, eqns->lhs + i*eqns->nvar);
            int testval = rhs - lower_dot;
            int diag = eqns->lhs[i*eqns->nvar + i];

            if(testval % diag)
                return 0;
                
            int result = testval / diag;

            if(result < 1 || result > 9)
                return 0;
            hits[i] = result;
            rhsz[i] = rhs;
            lhsz[i] = lower_dot;
        }
        printf("HIT!!!\n");
        
        printf("result: ");
        for(i = 0; i < eqns->neq; i++)
            printf("%3d", hits[i]);
        printf("\nrhs   : ");
        for(i = 0; i < eqns->neq; i++)
            printf("%3d", rhsz[i]);
        printf("\nlhs   : ");
        for(i = 0; i < eqns->neq; i++)
            printf("%3d", lhsz[i]);
        printf("\n");

        return 1;
    }

    int i;
    for(i = 0; i < 10; i++) {
        x[eqns->nvar - depth - 1] = i;
        int hit = checker2(AJ, eqns, x, depth+1);
        if(hit)
            return 1;
    }

    return 0;
}

int exhaust_nullspace_check(int AJ[10], eqn_t *eqns) {
    int *x = calloc(eqns->nvar,sizeof(int));

    int test = checker2(AJ, eqns, x, 0);
    free(x);

    return test;
}

int checker(int AJ[10], int next_index, int used, eqn_t *eqns, int *cnt) {
    int i;
    if(next_index == 10) {
        int test = test_eqns(AJ, eqns);
        int hit = 0;
        if(test) {
            hit = exhaust_nullspace_check(AJ, eqns);
        }

        if(hit) {
            for(i = 0; i < 10; i++)
                printf("%d ", AJ[i]);
            printf("\n");
        }
        return 0;
    }

    for(i = 0; i < 10; i++) {
        if(1 & (used >> i))
            continue;

        AJ[next_index] = i;
        checker(AJ, next_index+1, used | (1 << i), eqns, cnt);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("SYNTAX: %s kakuro_file.txt\n", argv[0]);
        exit(0);
    }

    FILE *fp = fopen(argv[1], "r");
    char buf[512];
    while(NULL != fgets(buf, sizeof(buf), fp)) {
        printf("line: %s", buf);

        int dim = atoi(buf);

        printf("dim: %d\n", dim);
        int nbox = dim*dim;
        char *p = buf + 2; // always start of first box
        int plen = strlen(p);
        int i;
        int inparens = 0;
        for(i = 0; i < plen; i++) {
            if(p[i] == '(')
                inparens = 1;
            if(p[i] == ')')
                inparens = 0;

            if(!inparens && (p[i] == ',' || p[i] == '\n'))
                p[i] = '\0';
        }

        box_t *puzz = calloc(nbox,sizeof(box_t));
        for(i = 0; i < nbox; i++) {
            int row = i / dim;
            int col = i % dim;

            box_t *box = puzz+i;

            printf("box[%d, %d]: %s\n", row, col, p);

            if(!strcmp(p, "X")) {
                box->type = gray;
                printf("\tgray\n");
            } else if(!strcmp(p, "O")) { 
                box->type = open;
                printf("\topen\n");
            } else if(strlen(p) == 1) {
                box->type = filled;
                box->fill[p[0]-'A'] = 1;
                printf("\tfill: ");
                int j;
                for(j = 0; j < 10; j++)
                    printf("%d,", box->fill[j]);
                printf("\n");
            } else {
                p++; // skip open paren
                int j;
                int neq = 1;
                int boxlen = strlen(p);
                for(j = 0; j < boxlen; j++)
                    if(p[j] == ',') {
                        p[j] = '\0';
                        neq = 2;
                    } else {
                        if(p[j] == ')')
                            p[j] = '\0';
                    }

                char eq[16];
                strcpy(eq, p);
                fill_eq(eq, box);
                p += strlen(p) + 1;

                if(neq == 2) {
                    strcpy(eq, p);
                    fill_eq(eq, box);
                    p += strlen(p) + 1;
                }
            }
            p += strlen(p) + 1;
        }
        ///// okay, puzzle is filled-in.  Now:
        // 1) create equations
        // 2) reduce equations
        // 3) exhaust A..J fills, looking for solutions
        
        eqn_t eqns;
        create_eqns(dim, puzz, &eqns);
        reduce_eqns(&eqns);

        int AJ[10];
        int cnt = 0;
        checker(AJ, 0, 0, &eqns, &cnt);
        
        printf("cnt: %d\n", cnt);
        free(puzz);
    }
    fclose(fp);
}
