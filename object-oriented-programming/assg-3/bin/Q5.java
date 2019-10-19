package bin;

public class Q5 {
    public static void main(String args[]) {
        U ob = new U();
        ob.methodK();
    }
}


interface K1 {
    public static final int intK = 1;

    public abstract void methodK();
}

interface K2 extends K1 {
    public abstract void methodK();
}

interface K3 extends K2 {
    public abstract void methodK();
}


class U implements K3 {
    public void methodK() {
        System.out.println(intK);
    }
}
