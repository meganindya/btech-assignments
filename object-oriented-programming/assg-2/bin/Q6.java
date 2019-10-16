package bin;

import static java.lang.System.*;

public class Q6 {
    public static void main(String args[]) {
        N obj = new N((float) 3.14, "PI", 3.14159);
        out.println(obj.ftype);
        out.println(obj.stype);
        out.println(obj.dtype);
    }
}

class M extends Object {
    protected float ftype;
    protected String stype;

    M(float ftype, String stype) {
        this.ftype = ftype;
        this.stype = stype;
    }
}

class N extends M {
    protected double dtype;

    N(float ftype, String stype, double dtype) {
        super(ftype, stype);
        this.dtype = dtype;
    }
}