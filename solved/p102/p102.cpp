#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(void)
{
	FILE *fp = fopen("data102.txt", "r");
	double pts[1000][6];

	int N = 1000;


	for(int k = 0; k < N; k++) {
		char buf[80];
		memset(buf, 0, 80*sizeof(char));
		int n = 0;
		bool eol = false;
		do {
			int j = 0;
			do {
				fread(buf + (j++), sizeof(char), 1, fp);
			} while(buf[j-1] != ',' && buf[j-1] != '\n');
			eol = buf[j-1] == '\n';
			buf[j-1] = '\0';
			pts[k][n++] = (double) atoi(buf);
		} while(!eol);
	}

	fclose(fp);

	int Nzero = 0;
	double m, b;
	bool inside;
	for(int k = 0; k < N; k++) {
		inside = true;
		m = (pts[k][3] - pts[k][1])/(pts[k][2] - pts[k][0]);
		b = pts[k][1] - m*pts[k][0];
		
		if((pts[k][5] < pts[k][4]*m + b && 0 > b) || (pts[k][5] > pts[k][4]*m + b && 0 < b))
			inside = false;

		m = (pts[k][5] - pts[k][1])/(pts[k][4] - pts[k][0]);
		b = pts[k][1] - m*pts[k][0];
		
		if((pts[k][3] < pts[k][2]*m + b && 0 > b) || (pts[k][3] > pts[k][2]*m + b && 0 < b))
			inside = false;

		m = (pts[k][5] - pts[k][3])/(pts[k][4] - pts[k][2]);
		b = pts[k][3] - m*pts[k][2];
		
		if((pts[k][1] < pts[k][0]*m + b && 0 > b) || (pts[k][1] > pts[k][0]*m + b && 0 < b))
			inside = false;

		Nzero += inside;
	}


	cout << "N inside: " << Nzero << endl;
	return 0;
}