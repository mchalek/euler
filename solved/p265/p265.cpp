#include <iostream>
#include <vector>

using namespace std;

// This program is not written flexibly, i.e. a lot of editing is required to 
// compute S(N) for N \neq 5.

long long S(const int n, const unsigned int str, const unsigned int used, const int bits[]);
bool check(const unsigned int str, const int bits[]);

int main(void)
{
	int bits[32];
	bits[0] = 1;
	for(int k = 1; k < 32; k++)
		bits[k] = bits[k-1] << 1;

	cout << "S(5) == " << S(5, 0, 1, bits) << endl; 
	return 0;
}

long long S(const int n, const unsigned int str, const unsigned int used, const int bits[])
{
// First generate a set of valid linear sequences, i.e. violations are allowed
// i.e. duplicate subsequences are allowed only if they require looping from the
// end to the beginning of the sequence.  These are generated by recursively adding
// bits to the end of the sequence and hashing all used subsequences to the bits of the
// integer used. 
// Once a valid linear sequence is generated, we must check for violations in the 
// circularized sequence using the check() function below.

	if(n == 32)
		return check(str, bits) ? str : 0;

	long long ret = 0;
	int ix0 = (str & 15) << 1;
	int ix1 = ix0 | 1;

	if(!(used & bits[ix0]))
		ret += S(n + 1, str << 1, used | bits[ix0], bits);
	
	if(!(used & bits[ix1]))
		ret += S(n + 1, (str << 1) | 1, used | bits[ix1], bits);

	return ret;
}

bool check(unsigned int str, const int bits[])
{
	// returns true if the input sequence str is a valid circular bit sequence.
	bool ret = true;
	int used = 1;
	int ix;
	int shift = 26;
	for(int k = 1; k < 28; k++) {
		ix = (str >> shift) & 31;
		used |= bits[ix];
		shift--;
	}

	str = (str & 15) << 4;

	shift = 3;
	for(int k = 0; k < 4; k++) {
		ix = (str >> shift) & 31;
		if(used & bits[ix]) {
			ret = false;
			break;
		}

		used |= bits[ix];
		shift--;
	}

	return ret;
}