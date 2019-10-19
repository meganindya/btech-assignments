import java.text.DecimalFormat;

public class Q7 {
    public static void main(String args[]) {
        Shape ob = new Shape() {
            public void display() {}
        };
        ob.instantiate();
    }
}


interface Shape2D {
    public double getArea();
}

interface Shape3D {
    public double getVolume();
}

interface Point3D {
    public static final int x = 3;
    public static final int y = 4;
    public static final int z = 5;
}

abstract class Shape implements Point3D {
    public abstract void display();

    public void instantiate() {
        Circle circle = new Circle();
        circle.display();

        Sphere sphere = new Sphere();
        sphere.display();
    }
}


class Circle extends Shape implements Shape2D {
    public double getArea() {
        double r = Math.sqrt(x * x + y * y + z * z);

        return (Math.PI * r * r);
    }

    public void display() {
        System.out.println("Area:\t" +
            new DecimalFormat("#.####").format(getArea()));
    }
}

class Sphere extends Shape implements Shape3D {
    public double getVolume() {
        double r = Math.sqrt(x * x + y * y + z * z);

        return (Math.PI * Math.pow(r, 3)) * 4 / 3;
    }

    public void display() {
        System.out.println("Volume:\t" +
            new DecimalFormat("#.####").format(getVolume()));
    }
}
