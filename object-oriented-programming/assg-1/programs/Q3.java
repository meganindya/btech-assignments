// Meganindya@Mega328p

import static java.lang.System.*;

class Q3 {
    public static void main(String args[]) {
        Circle c1 = new Circle(5.5);
        Circle c2 = new Circle(0.75);

        out.println("Radius\t\t: "      + c1.getRadius());
        out.printf("Perimeter\t: %.2f\n", c1.perimeter());
        out.printf("Area\t\t: %.2f\n\n" , c1.area());
        out.println("Radius\t\t: "      + c2.getRadius());
        out.printf("Perimeter\t: %.2f\n", c2.perimeter());
        out.printf("Area\t\t: %.2f\n\n" , c2.area());
    }
}

class Circle {
    private Double radius;

    Circle(Double radius) {
        this.radius = radius;
    }

    Double perimeter() {
        return 2 * Math.PI * radius;
    }

    Double area() {
        return Math.PI * Math.pow(radius, 2);
    }

    Double getRadius() {
        return this.radius;
    }
}
