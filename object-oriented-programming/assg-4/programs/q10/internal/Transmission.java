package programs.q10.internal;

import java.util.*;


public class Transmission {

    private String  type;
    private Integer speedCount;


    public void setType(String type) {
        this.type = type;
    }

    public void setSpeedCount(int speedCount) {
        this.speedCount = Integer.valueOf(speedCount);
    }


    public HashMap<String, Object> getProperties() {
        HashMap<String, Object> properties = new HashMap<>();

        properties.put("Transmission Type", (Object) type);
        properties.put("Speed Count",       (Object) speedCount);

        return properties;
    }

}
