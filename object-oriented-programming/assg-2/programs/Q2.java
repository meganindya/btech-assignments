import java.util.*;
import static java.lang.System.*;

public class Q2 {
    public static void main(String args[]) {
        int a = 100, b = 200;
        if(args.length >= 2) {
            try {
                a = Integer.parseInt(args[0]);
                b = Integer.parseInt(args[1]);
                if(!(a >= 2 && b >= 3 && a <= b))
                    throw new Exception("Error");
            }
            catch(Exception e) {
                out.println("..meh Invalid Arguments");
                out.println("Defaulting to 100 and 200");
                a = 100;
                b = 200;
            }
        }

        for(Integer i : new Primes(a, b).getPrimes())
            out.print(i.intValue() + " ");
        out.println();
    }
}

class Primes {
    private int a, b;
    private BitSet primes;
    private int count;

    Primes(int a, int b) {
        this.a = a;
        this.b = b;

        primes = new BitSet(b + 1);
        primes.set(0, b + 1);
        
        genPrimes();
    }

    public Integer[] getPrimes() {
        out.printf("%d primes between %d and %d\n", count, a, b);
        ArrayList<Integer> res = new ArrayList<Integer>();

        for(int i = a; i <= b; i++)
            if(primes.get(i))
                res.add(Integer.valueOf(i));

        return res.toArray(new Integer[res.size()]);
    }

    private void genPrimes() {
        int n = b;
        
        for(int i = 4; i <= n; i += 2)
            primes.clear(i);

        for(int i = 3; i <= (int) Math.sqrt(n); i += 2)
            for(int j = i * i; j <= n; j += i)
                primes.clear(j);

        count = primes.cardinality() -
                primes.get(0, a).cardinality();
    }
}