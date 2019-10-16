public class Q5 {
    public static void main(String args[]) {
        Rock rocks[] = new Rock[10];
        for(int i = 0; i < 10; i++) {
            int w = 1 + (int) Math.floor(Math.random() * 10);
            rocks[i] = new Rock(w);
        }

        for(int i = 0; i < 10; i++)
            System.out.printf("Rock %d has a mass of %d kg\n",
                (i + 1), rocks[i].getMass());

        System.out.printf("\nTotal mass is %d kg\n",
            Rock.getTotalMass());
    }
}

class Rock {
    private static int totalMass;
    private int mass;

    static {
        totalMass = 0;
    }

    Rock(int mass) {
        this.mass = mass;
        totalMass += mass;
    }

    int getMass() {
        return mass;
    }

    static int getTotalMass() {
        return totalMass;
    }
}