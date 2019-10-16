// Meganindya@Mega328p

package bin;

import static java.lang.Math.*;

public class Q6 {
    public static void main(String args[]) {
        int a = 3, b = 2, c = 5;
        if(args.length >= 3) {
            try {
                a = Integer.parseInt(args[0]);
                b = Integer.parseInt(args[1]);
                c = Integer.parseInt(args[2]);
            }
            catch(Exception e) {}
        }
        System.out.println("Solving for coefficients [" +
            a + ", " + b + ", " + c + "]");

        QuadraticEquation qe = new QuadraticEquation(a, b, c);
        qe.displaySol();
    }
}

class QuadraticEquation {
    private int a, b, c;
    private Complex v1, v2;

    QuadraticEquation(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;

        solveEquation();
    }

    void solveEquation() {
        Complex d = getDiscriminant();
        
        v1 = Complex.add(new Complex(-b, 0), d);
        v2 = Complex.sub(new Complex(-b, 0), d);

        v1 = Complex.reDiv(v1, 2);
        v2 = Complex.reDiv(v2, 2);
    }

    void displaySol() {
        System.out.printf("Roots : (%s, %s)\n",
            Complex.printComplex(v1), Complex.printComplex(v2));
    }

    Complex getDiscriminant() {
        double x = pow(b, 2);
        double y = 4 * a * c;

        Complex z = new Complex();
        if((x - y) < 0)
            z.im = sqrt(y - x);
        else if((x - y) == 0) {}
        else
            z.re = sqrt(x - y);

        return z;
    }
}

class Complex {
    double re, im;

    Complex() {
        re = im = 0.0;
    }

    Complex(double re, double im) {
        this.re = re;
        this.im = im;
    }

    static Complex add(Complex x, Complex y) {
        return new Complex(x.re + y.re, x.im + y.im);
    }

    static Complex sub(Complex x, Complex y) {
        return new Complex(x.re - y.re, x.im - y.im);
    }

    static Complex reDiv(Complex x, double y) {
        return new Complex(x.re / y, x.im / y);
    }

    static String printComplex(Complex v) {
        v.re = (double) round(v.re * 100d) / 100d;
        String s = printDouble(v.re);
        if(v.im == 0.0) return s;
        
        s += (v.im < 0) ? " - " : " + ";
        v.im = (double) round(v.im * 100d) / 100d;
        s += printDouble(abs(v.im)) + "i";

        return s;
    }

    static String printDouble(double v) {
        if(v % 1 == 0)
            return Integer.toString((int) floor(v));
        return Double.toString(v);
    }
}
