public class FactoredInt {
    public int N;
    public int factors[];
    public static Prime p = new Prime(100000);

    FactoredInt(int n)
    {
        N = n;
        factors = p.factor(n);
    }
}
