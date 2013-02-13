#include <iostream>
#include <cstring>
using namespace std;

int cycle_length(int);

int main(void)
{
	int max_len = 0, max_i = 0, curr_len = 0;
	for(int i = 2; i < 1000; i++) {
		curr_len = cycle_length(i);
		if(curr_len > max_len) {
			max_len = curr_len;
			max_i = i;
		}
	}
		
	cout << "longest cycle is 1/" << max_i << ", which has " << max_len << " repeat digits.\n";	

	return 0;
	
}

int cycle_length(int n)
{
	int max_remainder = n, ndig = 0;
	int curr_remainder, curr_quot;
	int *remainders = new int[1+max_remainder];
	memset(remainders, 0, (1+max_remainder)*sizeof(int));

	remainders[0] = 1;
	curr_remainder = 10 % n;	
	while(!remainders[curr_remainder]) // First get rid of any leading terms that will not be part of the repeat digits, eg the 1 in 1/6.
	{
		remainders[curr_remainder] = 1;
		curr_quot = (curr_remainder * 10) / n;
		curr_remainder = (curr_remainder * 10) % n;
	} 
	

	if(curr_remainder) { // don't do it if there is no cycle.
		memset(remainders, 0, (1+max_remainder)*sizeof(int));
		while(!remainders[curr_remainder])
		{
			remainders[curr_remainder] = 1;
			curr_quot = (curr_remainder * 10) / n;
			curr_remainder = (curr_remainder * 10) % n;
			ndig++;
			if(curr_quot > 9)
				ndig++;
			if(curr_quot > 99)
				ndig++;
			
		} 
	}

	return ndig;
}
