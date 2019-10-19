import static java.lang.System.*;

public class Q6 {
    public static void main(String args[]) {
        W ob = new W();
        out.println("Object implements L1: " + (ob instanceof L1));
        out.println("Object implements L2: " + (ob instanceof L2));
        out.println("Object implements L3: " + (ob instanceof L3));
        out.println("Object implements L4: " + (ob instanceof L4));
        out.println("Object extends W: " + (ob instanceof X));
    }
}


interface L1 {}

interface L2 {}

interface L3 extends L1, L2 {}

interface L4 {}


class X implements L3 {}

class W extends X implements L4 {}