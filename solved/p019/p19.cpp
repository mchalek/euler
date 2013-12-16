#include<cstdio>

int main(void)
{
	int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int currday = 1, counts = 0;

	for(int i = 1900; i <= 2000; i++) {
		if(i % 4 || (!(i % 100) && (i % 400)))
			days[1] = 28;
		else 
			days[1] = 29;

		for(int j = 0; j < 12; j++) {
			currday += days[j] % 7;
			currday = currday % 7;
			if(i > 1900 && currday == 0)
				counts++;
			
		}
	}

	printf("I count %d sundays on first of the month.\n", counts);

	return 0;
}
