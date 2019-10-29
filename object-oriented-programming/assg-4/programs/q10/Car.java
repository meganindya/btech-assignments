package programs.q10;

import programs.q10.internal.*;
import programs.q10.external.*;

import java.util.*;


public class Car {
    
    private String make;
    private String model;
    private String type;
    private String colour;

    private Engine          engine;
    private Transmission    transmission;
    private FuelSystem      fuelSystem;

    private Body            body;
    private Fittings        fittings;


    private HashMap<String, Object> properties;



    public Car(String make, String model, String type, String colour) {
        this.make   = make;
        this.model  = model;
        this.type   = type;
        this.colour = colour;

        engine = new Engine();
        transmission = new Transmission();
        fuelSystem = new FuelSystem();

        body = new Body();
        fittings = new Fittings();
    }


    public Engine configureEngine() {
        return engine;
    }

    public Transmission configureTransmission() {
        return transmission;
    }

    public FuelSystem configureFuelSystem() {
        return fuelSystem;
    }

    public Body configureBody() {
        return body;
    }

    public Fittings configureFittings() {
        return fittings;
    }


    public void generateProperties() {
        properties = new HashMap<>();

        properties.put("Make",      (Object) make);
        properties.put("Model",     (Object) model);
        properties.put("Type",      (Object) type);
        properties.put("Colour",    (Object) colour);

        properties.putAll(engine.getProperties());
        properties.putAll(transmission.getProperties());
        properties.putAll(fuelSystem.getProperties());
        properties.putAll(body.getProperties());
        properties.putAll(fittings.getProperties());
    }


    public void displayProperties() {
        generateProperties();

        for (Map.Entry<String, Object> entry : properties.entrySet())
            System.out.println(entry.getKey() + ":  " + entry.getValue());
    }

}
