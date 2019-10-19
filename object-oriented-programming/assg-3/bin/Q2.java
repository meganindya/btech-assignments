package bin;

import static java.lang.System.*;

public class Q2 {
    public static void main(String args[]) {
        Model1 model1 = new Model1();
        model1.display();

        Model2 model2 = new Model2();
        model2.display();

        Model3 model3 = new Model3();
        model3.display();
    }
}


interface AntiLockBrakes {
    public static final String description = "Anti-lock braking system (ABS) is a "
        + "safety anti-skid braking system used on aircraft and on land vehicles. "
        + "ABS operates by preventing the wheels from locking up during braking, "
        + "thereby maintaining tractive contact with the road surface.\n";

    public abstract void AntiLockBrakes();
}

interface CruiseControl {
    public static final String description = "Cruise control (or autocruise) is a "
        + "system that automatically controls the speed of a motor vehicle. The "
        + "system is a servomechanism that takes over the throttle of the car to "
        + "maintain a steady speed as set by the driver.\n";

    public abstract void CruiseControl();
}

interface PowerSteering {
    public static final String description = "A Power Steering system helps drivers "
        + "steer the vehicle by augmenting steering effort needed to turn the steering "
        + "wheel, making it easier for the driver to turn. Hydraulic or electric "
        + "actuators add controlled energy to the steering mechanism, so the driver "
        + "can provide less effort to turn the steered wheels.\n";

    public abstract void PowerSteering();
}

abstract class Auto implements AntiLockBrakes, CruiseControl, PowerSteering {
    public boolean featurePresent[] = new boolean[3];

    public void AntiLockBrakes() {
        out.println("Anti-lock braking system:");
        out.println(AntiLockBrakes.description);
    }

    public void CruiseControl() {
        out.println("Cruise control system:");
        out.println(CruiseControl.description);
    }

    public void PowerSteering() {
        out.println("Power steering system:");
        out.println(PowerSteering.description);
    }

    public void displayFeatures() {
        if (featurePresent[0])  AntiLockBrakes();
        if (featurePresent[1])  CruiseControl();
        if (featurePresent[2])  PowerSteering();
    }
}


class Model1 extends Auto {
    Model1() {
        featurePresent[0] = false;
        featurePresent[1] = false;
        featurePresent[2] = true;
    }

    public void display() {
        out.println("Model1\n======\nFeatures:\n");
        displayFeatures();
    }
}

class Model2 extends Auto {
    Model2() {
        featurePresent[0] = true;
        featurePresent[1] = true;
        featurePresent[2] = false;
    }

    public void display() {
        out.println("Model2\n======\nFeatures:\n");
        displayFeatures();
    }
}

class Model3 extends Auto {
    Model3() {
        featurePresent[0] = false;
        featurePresent[1] = true;
        featurePresent[2] = false;
    }

    void display() {
        out.println("Model3\n======\nFeatures:\n");
        displayFeatures();
    }
}
