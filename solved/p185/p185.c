#include <stdio.h>
#include <stdlib.h>

#define n 22

int r[] = { 56161856, 38474396, 58554629, 97428555, 42968496, 31742484, 45135590, 78909715, 81573563, 26152507,
				86900958, 63757119, 69138591, 64428890, 23213861, 23265094, 52515833, 17482704, 48957226, 30416311,
				18412364, 26598626};

int s[] = {50518293, 47293047, 40810587, 7068353, 43607543, 39465858, 94146117, 48908067, 44118483, 44386899, 
				51526254, 15077050, 73121360, 55042768,	4303845, 71271448, 79644322, 76758276, 52190306, 
				17224635, 54324589, 37316867};

int c[] = {2, 1, 3, 3, 3, 1, 2, 3, 1, 2, 3, 1, 1, 2, 0, 2, 2, 3, 1, 3, 3, 2}; 

struct pair {int i; unsigned long long k;};

int llcmp(const void *a, const void *b)
{
	return (((struct pair *) a) -> k < ((struct pair *) b) -> k) ? -1 :
		(((struct pair *) a) -> k > ((struct pair *) b) -> k) ? 1 : 0;
}

int main(void)
{
	int i, j, k, test, cscount=0, crcount=0;
	unsigned long long cb = 0, ncr, ncs, target;
	unsigned char r1[n], r2[n], r3[n], r4[n], r5[n], r6[n], r7[n], r8[n];
	unsigned char s1[n], s2[n], s3[n], s4[n], s5[n], s6[n], s7[n], s8[n];

	struct pair *cs, *cr;

	printf("Splitting data...");

	// first load data binary representations
	for(i = 0; i < n; i++) {
		r1[i] = r[i] % 10;
		r[i] /= 10;
		r2[i] = r[i] % 10;
		r[i] /= 10;
		r3[i] = r[i] % 10;
		r[i] /= 10;
		r4[i] = r[i] % 10;
		r[i] /= 10;
		r5[i] = r[i] % 10;
		r[i] /= 10;
		r6[i] = r[i] % 10;
		r[i] /= 10;
		r7[i] = r[i] % 10;
		r[i] /= 10;
		r8[i] = r[i] % 10;
		r[i] /= 10;

		s1[i] = s[i] % 10;
		s[i] /= 10;
		s2[i] = s[i] % 10;
		s[i] /= 10;
		s3[i] = s[i] % 10;
		s[i] /= 10;
		s4[i] = s[i] % 10;
		s[i] /= 10;
		s5[i] = s[i] % 10;
		s[i] /= 10;
		s6[i] = s[i] % 10;
		s[i] /= 10;
		s7[i] = s[i] % 10;
		s[i] /= 10;
		s8[i] = s[i] % 10;
		s[i] /= 10;

		cb |= (((unsigned long long) c[i]) << (42-2*i));
	}

	printf("Done.\nComputing tables...");

	// allocate memory for meet in middle
	cr = calloc(100000000, sizeof(struct pair));
	cs = calloc(100000000, sizeof(struct pair));

	if(!cr || !cs) {
		printf("Error: could not allocate memory.\n");
		exit(0);
	}

	for(i = 10000000; i < 100000000; i++) {
		test = i;
		cr[crcount].k = 0;
		cs[cscount].k = 0;
		for(j = 0; j < n; j++) {
			ncr  = r1[j] == (test % 10);
			ncr += r2[j] == ((test % 100      ) / 10);
			ncr += r3[j] == ((test % 1000     ) / 100);
			ncr += r4[j] == ((test % 10000    ) / 1000);
			ncr += r5[j] == ((test % 100000   ) / 10000);
			ncr += r6[j] == ((test % 1000000  ) / 100000);
			ncr += r7[j] == ((test % 10000000 ) / 1000000);
			ncr += r8[j] == ((test % 100000000) / 10000000);
			
			if(ncr > c[j]) {
				crcount--;
				break;
			}

			cr[crcount].i = i;
			cr[crcount].k |= ncr << (42-2*j);
		}

		for(j = 0; j < n; j++) {
			ncr  = s1[j] == (test % 10);
			ncr += s2[j] == ((test % 100      ) / 10);
			ncr += s3[j] == ((test % 1000     ) / 100);
			ncr += s4[j] == ((test % 10000    ) / 1000);
			ncr += s5[j] == ((test % 100000   ) / 10000);
			ncr += s6[j] == ((test % 1000000  ) / 100000);
			ncr += s7[j] == ((test % 10000000 ) / 1000000);
			ncr += s8[j] == ((test % 100000000) / 10000000);
			
			if(ncr > c[j]) {
				cscount--;
				break;
			}

			cs[cscount].i = i;
			cs[cscount].k |= ncr << (42-2*j);
		}
		cscount++;
		crcount++;
	}

	printf("Done.\n%d, %d valid values.\n", crcount, cscount);
	printf("Sorting tables...");
	fflush(stdout);
	
	qsort(cs, cscount, sizeof(struct pair), llcmp);

	printf("Done.\nSearching for result...\n");
	fflush(stdout);

	for(i = 0; i < crcount; i++) {
		j = 0; 
		k = cscount;
	
		target = cb - cr[i].k;

		while(j + 1 < k)
			if(target < cs[(j + k) / 2].k)
				k = (j + k) / 2;
			else
				j = (j + k) / 2;

		if(cr[i].k + cs[j].k == cb) {
			printf("Solution: %d%d; %011llx == (%011llx + %011llx)\n", cr[i].i, cs[j].i, cb, cr[i].k, cs[j].k);
			exit(0);
		}

		if(cr[i].k + cs[j + 1].k == cb) {
			printf("Solution: %d%d; %011llx == (%011llx + %011llx)\n", cr[i].i, cs[j+1].i, cb, cr[i].k, cs[j].k);
			exit(0);
		}

		//printf("Search on %08d (target %011llx) yielded %08d (%011llx).\n", cr[i].i, target, cs[j].i, cs[j].k);
	}

	printf("Solution not found.\n");

	free(cr);
	free(cs);
	return 0;
}
