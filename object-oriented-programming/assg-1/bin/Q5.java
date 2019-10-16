// Meganindya@Mega328p

package bin;

public class Q5 {
    public static void main(String args[]) {
        new Datatype((byte) 12);
        new Datatype((short) 1245);
        new Datatype(12445656);
        new Datatype(123456789012L);
    }
}

class Datatype {
    Datatype(byte a) {
        System.out.println("Byte\t" + a);
    }

    Datatype(short a) {
        System.out.println("Short\t" + a);
    }

    Datatype(int a) {
        System.out.println("Integer\t" + a);
    }

    Datatype(long a) {
        System.out.println("Long\t" + a);
    }
}
