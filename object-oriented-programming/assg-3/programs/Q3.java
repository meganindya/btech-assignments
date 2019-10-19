import static java.lang.System.*;

public class Q3 {
    public static void main(String args[]) {
        LuminousObject solid = new SolidObject();
        solid.lightsOn();
        solid.display();
        solid.lightsOff();
        solid.display();

        out.println();
        LuminousObject cone = new LuminousCone();
        cone.lightsOn();
        cone.display();
        cone.lightsOff();
        cone.display();

        out.println();
        LuminousObject cube = new LuminousCube();
        cube.lightsOn();
        cube.display();
        cube.lightsOff();
        cube.display();
    }
}


interface LuminousObject {
    public abstract void display();

    public abstract void lightsOn();
    public abstract void lightsOff();
}

class SolidObject implements LuminousObject {
    public String type;
    public boolean illuminated;

    public void lightsOn() {
        illuminated = true;
    }

    public void lightsOff() {
        illuminated = false;
    }

    public void display() {
        if (illuminated)
            out.println("Illuminated Solid");
        else
            out.println("Obfuscated Solid");
    }
}


class Cone extends SolidObject {
    Cone() {
        type = "Cone";
    }

    public void display() {
        out.println("Cone");
    }
}

class LuminousCone extends Cone implements LuminousObject {
    public void display() {
        if (illuminated)
            out.println("Illuminated " + type);
        else
            out.println("Obfuscated " + type);
    }
}


class Cube extends SolidObject {
    Cube() {
        type = "Cube";
    }

    public void display() {
        out.println("Cube");
    }
}

class LuminousCube extends Cube implements LuminousObject {
    public void display() {
        if (illuminated)
            out.println("Illuminated " + type);
        else
            out.println("Obfuscated " + type);
    }
}