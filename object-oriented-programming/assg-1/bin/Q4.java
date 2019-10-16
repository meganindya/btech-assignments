// Meganindya@Mega328p

package bin;

public class Q4 {
    public static void main(String args[]) {
        int dist1 = 25;
        int dist2 = 42;

        if(args.length >= 2) {
            try {
                int v;
                if((v = Integer.parseInt(args[0])) >= 0)
                    dist1 = v;
                else    throw new Exception("Error");
                if((v = Integer.parseInt(args[1])) >= 0)
                    dist2 = v;
                else    throw new Exception("Error");
            }
            catch(Exception e) {
                System.out.println("Using default distances");
            }
        }
        else    System.out.println("Using default distances");

        int dist = Maths.sum(dist1, dist2);
        System.out.println(dist1 + " + " + dist2 + " = " + dist);
    }
}

class Maths {
    public static int sum(int  a, int b) {
        return a + b;
    }
}
