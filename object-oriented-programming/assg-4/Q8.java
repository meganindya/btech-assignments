import packQ8.circle.*;
import packQ8.square.*;
import packQ8.triangle.*;

import static java.lang.System.*;

public class Q8 {
    public static void main(String args[]) {
        double radius = packQ8.circle.Dim.radius;
        Circle cir = new Circle(radius);
        double areaC = cir.area();

        out.println("\fCircle of radius " + radius);
        out.println("Area: " + areaC);



        double side = packQ8.square.Dim.side;
        Square sqr = new Square(side);
        double areaS = sqr.area();

        out.println("\nSquare of side " + side);
        out.println("Area: " + areaS);



        double height = packQ8.triangle.Dim.height;
        double base = packQ8.triangle.Dim.base;
        Triangle trl = new Triangle(height, base);
        double areaT = trl.area();

        out.println("\nTriangle of height " + height + " and base " + base);
        out.println("Area: " + areaT);
    }
}