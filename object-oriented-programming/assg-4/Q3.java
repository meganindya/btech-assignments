class Q3 {
    public static void main(String args[]) {
        int a = 7, b = 3, c = 0;

        try {
            c = a / (b >> 2);
        }
        catch (ArithmeticException e) {
            System.out.println("Error: " + e.getMessage());
            return;
        }

        System.out.println(c);
    }
}