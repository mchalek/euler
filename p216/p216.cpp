#include<iostream>
using namespace std;

#define NTEST 100
#define MAX_CHECK 3*NTEST

int main(void)
{
	int nprimes = 0;
	int i, j, k, jmin, p;
	long long t;
	int N = 0;
	int dpmax = 0;
	bool ok;
	int *iscomposite = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *prime_list = (int *) calloc(MAX_CHECK+1, sizeof(int));
	int *tmp = (int *) calloc(MAX_CHECK+1, sizeof(int));
	char *checked = (char *) calloc(NTEST+1, sizeof(char));
	char *pcount = (char *) calloc(MAX_CHECK+1, sizeof(char));

	for(i = 2; i <= MAX_CHECK; i++)
		if(!iscomposite[i]) {
			prime_list[nprimes++] = i;
			for(j = 2*i; j <= MAX_CHECK; j += i)
				iscomposite[j] = 1;
		}

	cout << "Prime list calculated.\n";
	jmin = 0;
	for(int n = 2; n <= NTEST; n++) {
		if(!checked[n]) {
			ok = true;
			t = 2*((long long) n)*((long long) n)-1;
	
			j = 0;
			while(ok && prime_list[j] < 2*n)
				ok = (t % prime_list[++j]) ? true : false;
			
			if(!ok) {
				p = prime_list[j];
				for(k = n + p; k <= NTEST; k += p)
					checked[k] = 0;

				p = (int) t / prime_list[j];
				for(k = n + p; k <= NTEST; k += p)
					checked[k] = 0;
				
				cout << "Found a number [t(" << n << ") == " << t << "] divisible by " << prime_list[j] << endl;
			} else {
				N++;
				p = t;
				for(k = n + p; k <= NTEST; k += p)
					checked[k] = 0;
			}
						
			if(n > prime_list[jmin]) {
				cout << "Getting rid of " << prime_list[jmin] << endl;
				jmin++;
			}
		} 
	}

	cout << "Answer: " << N << endl;
	return 0;
}