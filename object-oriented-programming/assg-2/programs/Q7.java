public class Q7 {
    public static void main(String args[]) {
        H ob = new H(8, 22);
        ob.display();
    }
}

class G {
    protected static int x;

    G(int x) {
        G.x = x;
    }
}

class H extends G {
    protected int x;

    H(int g, int h) {
        super(g);
        x = h;
    }

    void display() {
        System.out.println("Variable x in G : " + G.x);     // super.x works, but not ideal
        System.out.println("Variable x in H : " + this.x);  // x works just fine
    }
}