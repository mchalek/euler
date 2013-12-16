#include<cstdio>
#include<cstdlib>
#include<cstring>

int comparator(const void *, const void *);

int main(void)
{
	char **names = (char **) malloc(6000*sizeof(char *));
	char buf;
	int nnames=0, nlen, currscore, totscore=0;
	FILE *fin = fopen("data22.txt", "r");
	while(!feof(fin)) {
		names[nnames] = (char *) malloc(40*sizeof(char));
		nlen = 0;
		do {
			fread(&buf, sizeof(char), 1, fin);
			if(buf >= 'A' && buf <= 'Z')
				names[nnames][nlen++] = buf;
		} while(buf != ',' && !feof(fin));
		names[nnames++][nlen] = '\0';
	}

	qsort(names, nnames, sizeof(char *), comparator);

	for(int i = 0; i < nnames; i++) {
		currscore = 0;
		for(int j = 0; j < strlen(names[i]); j++)
			currscore += names[i][j] - 'A' + 1;
		totscore += currscore * (i+1);
	}
	printf("total name score: %d\n", totscore);

	return 0;
}

int comparator(const void *a, const void *b)
{
	return strcmp(*((char **) a), *((char **) b));
}