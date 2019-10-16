public class Q9 {
    public static void main(String args[]) {
        Fruit A = new Apple("Pear Green");
        Fruit B = new Banana("Yellow Ochre");
        Fruit O = new Orange("Tangerine");
        Fruit S = new Strawberry("Cardinal Red");

        A.display();
        B.display();
        O.display();
        S.display();
    }
}

abstract class Fruit {
    protected String colour;

    public abstract String toString();

    void display() {
        System.out.println(toString());
    }
}

class Apple extends Fruit {
    private static final String type = "Apple";

    Apple(String colour) {
        super.colour = colour;
    }

    public String toString() {
        return "Fruit : " + type + "\t\tColour : " + colour;
    }
}

class Banana extends Fruit {
    private static final String type = "Banana";

    Banana(String colour) {
        super.colour = colour;
    }

    public String toString() {
        return "Fruit : " + type + "\t\tColour : " + colour;
    }
}

class Orange extends Fruit {
    private static final String type = "Orange";

    Orange(String colour) {
        super.colour = colour;
    }

    public String toString() {
        return "Fruit : " + type + "\t\tColour : " + colour;
    }
}

class Strawberry extends Fruit {
    private static final String type = "Strawberry";

    Strawberry(String colour) {
        super.colour = colour;
    }

    public String toString() {
        return "Fruit : " + type + "\tColour : " + colour;
    }
}