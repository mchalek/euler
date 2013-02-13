public class HelloWorld {
    public static void main(String[] args) {
        Prime p = new Prime(100000);
        System.out.printf("there are %d primes below 100000\n", p.getNPrimes());

        int f[] = p.factor(1102);
        System.out.printf("Prime factorization of 1102: ");
        for(int i = 0; i < f.length; i++)
            System.out.printf("%d ", f[i]);
        System.out.printf("\n");

        FactoredInt fi[] = new FactoredInt[100001];
        for(int i = 0; i < 100001; i++)
            fi[i] = new FactoredInt(i);

        System.out.printf("Factorization of 43401: ");
        for(int i = 0; i < fi[43401].factors.length; i++)
            System.out.printf("%d ", fi[43401].factors[i]);
        System.out.printf("\n");
    }
}

