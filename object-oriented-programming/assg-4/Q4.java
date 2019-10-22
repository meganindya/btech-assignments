import static java.lang.System.*;

class Q4 {
    public static void main(String args[]) {
        int n = 0xFF, c, d;
        int a[] = {2, 3, 0, 5, 0};

        c = d = 1;

        out.println("n = " + n);
        
        out.print("d in [ ");
        for (int i : a)   out.print(i + " ");
        out.println("]");

        try {
            try {
                int i = 1 + (int) (Math.random() * 8);
                out.println("index: " + i);
                
                d = a[i];
                out.println("d = " + d);
            }
            catch (ArrayIndexOutOfBoundsException e) {
                out.println("Error: index out of range");
                return;
            }

            c = n / d;
            out.printf("n / d = %d\n", c);
        }
        catch (ArithmeticException e) {
            out.println("Error: / by zero");
        }
    }
}