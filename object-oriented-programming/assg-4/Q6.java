import static java.lang.System.*;

class Q6 {
    public static void main(String args[]) {
        int a[] = {1, 2, 3, 4, 5};
        out.print("a : [ ");
        for (int i : a) out.print(i + " ");
        out.println("]");

        for (int i = 0; i < 8; i++) {
            out.printf("Index %d : ", i);

            try {
                out.println(a[i]);
            }
            catch (ArrayIndexOutOfBoundsException e) {
                out.println("index out of bounds");
            }
        }
    }
}