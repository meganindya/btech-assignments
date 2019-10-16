package bin;

import static java.lang.System.*;

public class Q4 {
    public static void main(String args[]) {
        new Circle(5.45).display();
        new Circle(5.45, 1.21, 2.78).display();
        new Circle(3, 4, 5).display();
        new Circle(1, 3.45, 6.113).display();
    }
}

class Circle {
    Double abs;
    Double ord;
    Double rad;

    Circle(double rad) {
        this.rad = Double.valueOf(rad);
    }

    Circle(double abs, double ord, double rad) {
        this.abs = Double.valueOf(abs);
        this.ord = Double.valueOf(ord);
        this.rad = Double.valueOf(rad);
    }

    void display() {
        String r = getString(rad);
        out.printf("Circle of radius %s, ", r);

        if(abs == null && ord == null)
            out.println("centred at origin");
        else {
            String x = getString(abs);
            String y = getString(ord);
            out.printf("centred at (%s, %s)\n", x, y);
        }
    }

    static String getString(Double n) {
        if(n % 1 == 0)
            return Integer.toString((int) Math.floor(n));
        else
            return Double.toString(n);
    }
}