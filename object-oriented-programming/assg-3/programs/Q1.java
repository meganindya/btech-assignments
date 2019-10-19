import static java.lang.System.*;

public class Q1 {
    // driver
    public static void main(String args[]) {
        // anonymous subclass of abstact class MatObject
        MatObject ob = new MatObject() {};
        ob.instantiation();
    }
}


interface Material {
    // constants
    public static final String matBall = "Leather";
    public static final String matCoin = "Nickel";
    public static final String matRing = "Gold";
}

abstract class MatObject implements Material {
    public String material;

    // instantiates subclasses which however,
    // still extend this class
    public void instantiation() {
        Ball ball = new Ball(matBall);
        ball.display();

        Coin coin = new Coin(matCoin);
        coin.display();

        Ring ring = new Ring(matRing);
        ring.display();
    }
}


// concrete subclasses
class Ball extends MatObject {
    Ball(String material) {
        super.material = material;
    }

    protected void display() {
        out.println("Ball is made of " + material);
    }
}

class Coin extends MatObject {
    Coin(String material) {
        super.material = material;
    }

    protected void display() {
        out.println("Coin is made of " + material);
    }
}

class Ring extends MatObject {
    Ring(String material) {
        super.material = material;
    }

    protected void display() {
        out.println("Ring is made of " + material);
    }
}
