package programs.q10.internal;

import java.util.*;


public class FuelSystem {
    
    private Integer tankCapacity;
    private String  fuelType;


    public void setTankCapacity(int tankCapacity) {
        this.tankCapacity = Integer.valueOf(tankCapacity);
    }

    public void setFuelType(String fuelType) {
        this.fuelType = fuelType;
    }


    public HashMap<String, Object> getProperties() {
        HashMap<String, Object> properties = new HashMap<>();

        properties.put("Tank Capacity", (Object) tankCapacity);
        properties.put("Fuel Type",     (Object) fuelType);

        return properties;
    }

}
