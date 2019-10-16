package bin;

import static java.lang.System.*;

public class Q1 {
    public static void main(String args[]) {
        int n = 15;
        if(args.length != 0) {
            try {
                n = Integer.parseInt(args[0]);
                if(n <= 0)  throw new Exception("Error");
            }
            catch(Exception e) {
                out.println("Defaulting to 10 elements");
                n = 10;
            }
        }
        
        int fib[] = new Fibonacci(n).genFibonacci();

        for(int i : fib)    out.print(i + " ");
        out.println();
    }
}

class Fibonacci {
    private int n;
    private int fibonacci[];

    Fibonacci(int n) {
        this.n = n;
        fibonacci = new int[n];
    }

    public int[] genFibonacci() {
        fibonacci[0] = 0;
        if(n > 1) {
            fibonacci[1] = 1;
            for(int i = 2; i < n; i++)
                fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }

        return fibonacci;
    }
}