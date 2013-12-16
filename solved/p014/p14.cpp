#include<cstdio>
#include<cstring>
#include<cstdlib>

int main(void)
{
	int maxLen = 0, maxNum = 0, currLen, j;
	long long currNum;
	int *seq = (int *) calloc(10000, sizeof(int));
	for(int i = 1; i < 1000000; i++) {
		currLen = 1; // for the 1 that each sequence will end with
		currNum = i;
		while(currNum != 1) {
			seq[currLen++] = currNum;		
			currNum = (currNum % 2) ? 3*currNum + 1 : currNum / 2;
		}
		if(currLen > maxLen) {
			maxLen = currLen;
			maxNum = i;
		}
	}
	printf("max length %d achieved from %d\n", maxLen, maxNum);
	return 0;
}