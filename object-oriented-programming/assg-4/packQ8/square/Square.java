package packQ8.square;

public class Square {
    private double side;

    public Square(double side) {
        this.side = side;
    }
    public double area() {
        return (side * side);
    }
}