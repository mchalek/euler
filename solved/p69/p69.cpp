#include <vector>
#include <iostream>
using namespace std;

#define N 1000000

int main(void)
{
    vector<bool> iscomp(N+1);

    vector<int> my_primes[N+1];

    vector<int> tot(N+1); // totient 

    double maxrat = 0;
    double maxi = 0;

    long i;
    for(i = 2; i <= N; i++) {
        if(!iscomp[i]) {
            long j;
            my_primes[i].push_back(i);

            for(j = 2*i; j <= N; j += i) {
                my_primes[j].push_back(i);
                iscomp[j] = true;
            }
        }

        long j;
        tot[i] = i;
        for(j = 0; j < my_primes[i].size(); j++) {
            tot[i] /= my_primes[i][j];
            tot[i] *= my_primes[i][j]-1;
        }

        double rat = ((double) i) / tot[i];
        if(rat > maxrat) {
            maxrat = rat;
            maxi = i;
        }
    }

    cout << "n == " << maxi << " maximizes n/\\phi(n) (" << maxrat << ") for n <= " << N << endl;

    return 0;
}
