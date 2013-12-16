#include <cstdio>
#include <cstring>
#include <cstdlib>

//#define __DEBUG

int main(void)
{
#ifdef __DEBUG
	FILE *fin = fopen("data83debug.txt", "r");
	int M[5][5];
	int S[5][5];
	int N = 5;
#else
	FILE *fin = fopen("data83.txt", "r");
	int M[80][80];
	int S[80][80];
	int N = 80;
#endif
	char buf[80];
	int j, k = 0, l = 0;
	while(!feof(fin)) {
		memset(buf, 0, sizeof(char));
		j = 0;
		do {
			fread(buf + (j++), sizeof(char), 1, fin);
		} while(buf[j-1] != ',' && buf[j-1] != '\n' && !feof(fin));
		if(!feof(fin)) {
			if(buf[j-1] == '\n') {
				buf[j-1] = '\0';
				M[k][l] = atoi(buf);
				k++;
				l = 0;
			} else {
				buf[j-1] = '\0';
				M[k][l] = atoi(buf);
				l++;
			}
		}
	}

	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			S[x][y] = 1000000000;
#ifdef __DEBUG
			printf("%d ", M[x][y]);
#endif
		}
#ifdef __DEBUG
		printf("\n");
#endif
	}
	S[0][0] = M[0][0];

	fclose(fin);

	int x = 1;
	bool backtrack;
	while(x < N) {
		backtrack = false;
		// First the forward pass; movement from x-1 to x shell, but not within x shell
		for(j = 0; j < x; j++) {
			if(S[x-1][j] + M[x][j] < S[x][j])
				S[x][j] = S[x-1][j] + M[x][j];

			if(S[j][x-1] + M[j][x] < S[j][x])
				S[j][x] = S[j][x-1] + M[j][x];

			if(x < N-1) {
				if(S[j][x+1] + M[j][x] < S[j][x]) {
					S[j][x] = S[j][x+1] + M[j][x];
					backtrack = true;
				}

				if(S[x+1][j] + M[x][j] < S[x][j]) {
					S[x][j] = S[x+1][j] + M[x][j];
					backtrack = true;
				}
			}
		}

		if(S[x-1][x] + M[x][x] < S[x][x])
			S[x][x] = S[x-1][j] + M[x][x];

		if(S[x][x-1] + M[x][x] < S[x][x])
			S[x][x] = S[x][x-1] + M[x][x];
		
		if(x < N-1) {
			if(S[x+1][x] + M[x][x] < S[x][x]) {
				S[x][x] = S[x+1][x] + M[x][x];
				backtrack = true;
			}
		
			if(S[x][x+1] + M[x][x] < S[x][x]) {
				S[x][x] = S[x][x+1] + M[x][x];
				backtrack = true;
			}
		}

// Now allow down/right movement within shell x
		for(j = 0; j < x; j++) {
			if(S[j][x] + M[j+1][x] < S[j+1][x]) {
				S[j+1][x] = S[j][x] + M[j+1][x];
				backtrack = true;
			}
			if(S[x][j] + M[x][j+1] < S[x][j+1]) {
				S[x][j+1] = S[x][j] + M[x][j+1];
				backtrack = true;
			}
		}
// At this point we know that S[x][x] is optimized for the x shell. Check to see if any up/left
// movement is necessary.
		for(j = x; j; j--) {
			if(S[j][x] + M[j-1][x] < S[j-1][x]) {
				S[j-1][x] = S[j][x] + M[j-1][x];
				backtrack = true;
			}

			if(S[x][j] + M[x][j-1] < S[x][j-1]) {
				S[x][j-1] = S[x][j] + M[x][j-1];
				backtrack = true;
			}

		}

		backtrack ? x-- : x++;
#ifdef __DEBUG
		printf("x == %d\n", x);
#endif
	}
#ifdef __DEBUG
	printf("\nHere is the minimal sum square:\n");
	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			printf("%d ", S[x][y]);
		}
		printf("\n");
	}
#else
	printf("Minimal sum: %d\n", S[N-1][N-1]);
#endif
	return 0;
}