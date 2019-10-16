import static java.lang.System.*;

public class Q11 {
    public static void main(String args[]) {
        Monster monsters[] = new Monster[6];
        monsters[0] = new Zombie();
        monsters[1] = new Werewolf();
        monsters[2] = new Werewolf();
        monsters[3] = new Vampire();
        monsters[4] = new Zombie();
        monsters[5] = new Vampire();

        for(int i = 0; i < 6; i++) {
            out.print("Monster " + (i + 1) + " is a ");
            monsters[i].display();
        }
    }
}

abstract class Monster {
    protected String type;

    abstract void display();
}

class Vampire extends Monster {
    private static boolean called = false;

    Vampire() {
        type = "Vampire";
    }

    void display() {
        out.println(type);
        if(called)  return;
        out.println("Vampires subsist by feeding " +
            "on the vital force of the living");
        called = true;
    }
}

class Werewolf extends Monster {
    private static boolean called = false;

    Werewolf() {
        type = "Werewolf";
    }

    void display() {
        out.println(type);
        if(called)  return;
        out.println("Werewolf is a human with " +
            "the ability to shapeshift into a wolf");
        called = true;
    }
}

class Zombie extends Monster {
    private static boolean called = false;

    Zombie() {
        type = "Zombie";
    }

    void display() {
        out.println(type);
        if(called)  return;
        out.println("Zombie is an undead being " +
            "created through the reanimation of a corpse");
        called = true;
    }
}