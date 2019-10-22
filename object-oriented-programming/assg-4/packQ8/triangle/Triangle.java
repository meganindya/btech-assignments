package packQ8.triangle;

public class Triangle {
    private double height;
    private double base;

    public Triangle(double height, double base) {
        this.height = height;
        this.base = base;
    }
    public double area() {
        return (0.5 * base * height);
    }
}