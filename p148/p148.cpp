#include<iostream>
#include<cstring>
using namespace std;

#define NROWS 70
int main(void)
{
	char *row0, *row1, *tmp;
	row0 = (char *) malloc((NROWS+2)*sizeof(char));
	row1 = (char *) malloc((NROWS+2)*sizeof(char));
	long long brutecount = 0, rowcount = 0;
	int k, n;
	memset(row0, 0, (NROWS+2)*sizeof(char));
	memset(row1, 0, (NROWS+2)*sizeof(char));
	row1[0] = 1;
	for(n = 1; n <= NROWS; n++) {
		row0[0] = 1;
		rowcount = 0;
		for(k = 1; k < n/2; k++) {
			row0[k] = (row1[k] + row1[k-1]) % 7;
			rowcount += 2*!row0[k];
		}
		if(n % 2 && n > 1) {
			row0[n/2] = (2*row1[n/2-1]) % 7;
			rowcount += !row0[n/2];
		}

		for(k = 0; k <= n / 2; k++)
			cout << (int) row0[k] << " ";

		cout << endl;
		tmp = row0;
		row0 = row1;
		row1 = tmp;
		brutecount += rowcount;
	}

	cout << "counted by brute force: " << brutecount << endl;
	return 0;
}
