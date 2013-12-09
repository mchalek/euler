public class Prime {
    private boolean isprime[];
    private int primes[];
    private int n;
    Prime(int N) {
        n = N;
        int j;
        int nprimes = 0;
        isprime = new boolean[n];

        boolean iscomp[] = new boolean[n];

        for(int i = 2; i < n; i++) {
            if(false == iscomp[i]) {
                isprime[i] = true;
                nprimes++;
                for(j = 2*i; j < n; j += i)
                    iscomp[j] = true;
            }
        }
        
        primes = new int[nprimes];

        j = 0;
        for(int i = 0; i < n; i++) {
            if(isprime[i])
                primes[j++] = i;
        }
    }

    public boolean check(int k)
    {
        if(k < n)
            return isprime[k];
        else
            return false;
    }

    public int getNPrimes()
    {
        return primes.length;
    }

    public int[] factor(int k)
    {
        int factors[] = new int[primes.length];
        int maxfactor = 0;
        int nfactors = 0;
        int m;
        for(int i = 0; i < primes.length && k > 1; i++) {
            while((k % primes[i]) == 0) {
                factors[i]++;
                k /= primes[i];
                maxfactor = i;
                nfactors++;
            }
        }
        int ret[] = new int[nfactors];
        m = 0;
        for(int i = 0; i <= maxfactor; i++) {
            for(int j = 0; j < factors[i]; j++)
                ret[m++] = primes[i];

        }
        return ret;
    }
}
