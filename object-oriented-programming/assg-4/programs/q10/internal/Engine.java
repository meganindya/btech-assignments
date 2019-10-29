package programs.q10.internal;

import java.util.*;


public class Engine {

    private String  type;
    private Integer cylinderCount;
    private Integer displacement;



    public void setType(String type) {
        this.type = type;
    }

    public void setCylinderCount(int cylinderCount) {
        this.cylinderCount = Integer.valueOf(cylinderCount);
    }

    public void setDisplacement(int displacement) {
        this.displacement = Integer.valueOf(displacement);
    }


    public HashMap<String, Object> getProperties() {
        HashMap<String, Object> properties = new HashMap<>();

        properties.put("Engine Type",   (Object) type);
        properties.put("Cylinders",     (Object) cylinderCount);
        properties.put("Displacement",  (Object) displacement);

        return properties;
    }

}
