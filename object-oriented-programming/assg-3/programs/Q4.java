import static java.lang.System.*;

public class Q4 {
    public static void main(String args[]) {
        Q ob = new Q();
        ob.displayP();
        ob.displayP1();
        ob.displayP2();
        ob.displayP12();
    }
}


interface P {
    public static final String valP = "P";

    public void displayP();
}

interface P1 extends P {
    public static final String valP1 = "P1";

    public void displayP1();
}

interface P2 extends P {
    public static final String valP2 = "P2";

    public void displayP2();
}

interface P12 extends P1, P2 {
    public static final String valP12 = "P12";

    public void displayP12();
}


class Q implements P12 {
    public void displayP() {
        out.println(valP);
    }

    public void displayP1() {
        out.println(valP1);
    }

    public void displayP2() {
        out.println(valP2);
    }

    public void displayP12() {
        out.println(valP12);
    }
}