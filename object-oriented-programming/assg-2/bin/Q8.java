package bin;

import static java.lang.System.*;

public class Q8 {
    public static void main(String args[]) {
        new U(3, 5, 7);
    }
}

class S {
    protected int s1;

    S(int s1) {
        this.s1 = s1;
        out.println("Class S \t s1 : " + this.s1);
    }
}

class T extends S {
    protected int t1;

    T(int s1, int t1) {
        super(s1);
        this.t1 = t1;
        out.println("Class T \t t1 : " + this.t1);
    }
}

class U extends T {
    protected int u1;

    U(int s1, int t1, int u1) {
        super(s1, t1);
        this.u1 = u1;
        out.println("Class U \t u1 : " + this.u1);
    }
}