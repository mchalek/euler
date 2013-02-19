#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

#define N 40000000

int chainlen(long a, const int phi[])
{
    int len = 1;
    while(len < 26 && a > 1) {
        a = phi[a];
        len++;
    }

    return len;
}


int main(void)
{
    vector<bool> iscomp(N);

    vector<int> my_primes[N];

    int *pprod = new int[N];
    int *pm1prod = new int[N];

    int *phi = new int[N];
    memset(phi, 0, (N)*sizeof(int));

    long sum = 0;

    long i;
    for(i = 0; i < N; i++) {
        pprod[i] = 1;
        pm1prod[i] = 1;
    }
    for(i = 2; i < N; i++) {
        if(!iscomp[i]) {
            long j;
            pprod[i] = i;
            pm1prod[i] = i-1;

            for(j = 2*i; j < N; j += i) {
                pprod[j] *= i;
                pm1prod[j] *= i-1;
                iscomp[j] = true;
            }
        }

        long j;
        phi[i] = i/pprod[i]*pm1prod[i];

        if(!iscomp[i]) {
            if(25 == chainlen(i, phi)) {
                sum += i;
            }
        }
    }

    cout << "ans: " << sum << endl;

    return 0;
}
