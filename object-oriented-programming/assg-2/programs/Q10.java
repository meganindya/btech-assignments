public class Q10 {
    public static void main(String args[]) {
        Airplane A1 = new B747(416, "21744VN3");
        Airplane A2 = new B757(295, "21864LN1");
        Airplane A3 = new B767(185, "21862LN2");

        A1.display();
        A2.display();
        A3.display();
    }
}

abstract class Airplane {
    protected int capacity;
    protected String serial;

    Airplane(int capacity, String serial) {
        this.capacity = capacity;
        this.serial = serial;
    }

    public abstract String toString();

    void display() {
        System.out.println(toString());
    }
}

class B747 extends Airplane {
    private static final String type = "B747";

    B747(int capacity, String serial) {
        super(capacity, serial);
    }

    public String toString() {
        return "Type : " + type + "   Capacity : " +
            capacity + "   Serial : " + serial;
    }
}

class B757 extends Airplane {
    private static final String type = "B757";

    B757(int capacity, String serial) {
        super(capacity, serial);
    }

    public String toString() {
        return "Type : " + type + "   Capacity : " +
            capacity + "   Serial : " + serial;
    }
}

class B767 extends Airplane {
    private static final String type = "B767";

    B767(int capacity, String serial) {
        super(capacity, serial);
    }

    public String toString() {
        return "Type : " + type + "   Capacity : " +
            capacity + "   Serial : " + serial;
    }
}