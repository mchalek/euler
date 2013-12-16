#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

#define N 10000000

bool isperm(long a, long b)
{
    char dcounta[10];
    char dcountb[10];

    memset(dcounta, 0, sizeof(dcounta));
    memset(dcountb, 0, sizeof(dcountb));

    while(a) {
        dcounta[a % 10]++;
        a /= 10;
    }

    while(b) {
        dcountb[b % 10]++;
        b /= 10;
    }

    for(int i = 0; i < 10; i++)
        if(dcounta[i] != dcountb[i])
            return false;

    return true;
}

int main(void)
{
    vector<bool> iscomp(N+1);

    vector<int> my_primes[N+1];

    double minrat = HUGE_VAL;
    long mini = 0;

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
        long tot = i;
        for(j = 0; j < my_primes[i].size(); j++) {
            tot /= my_primes[i][j];
            tot *= my_primes[i][j]-1;
        }

        if(isperm(i, tot)) {
            double rat = ((double) i) / tot;
            if(minrat > rat) {
                minrat = rat;
                mini = i;
            }
        }
    }

    cout << "ans: " << mini << endl;

    return 0;
}
