// Meganindya@Mega328p

class Q7 {
    public static void main(String args[]) {
        new Extra();
    }
}

class Extra {
    private String s;

    Extra() {
        this("Robert Downey Jr. was a better Sherlock Holmes");
    }

    Extra(String s) {
        System.out.println(s);
        this.s = "No further questions";
        this.display(this);
    }

    void display(Extra ob) {
        System.out.println(ob.s);
    }
}
