package programs.q10;

public class Q10 {
    public static void main(String args[]) {
        Car cars[] = new Car[5];

        cars[0] = new Car("BMW", "Z4", "Coupe", "Misano Blue Metallic");
        
        cars[0].configureEngine().setType("TwinPower Turbo");
        cars[0].configureEngine().setCylinderCount(6);
        cars[0].configureEngine().setDisplacement(2998);

        cars[0].configureTransmission().setSpeedCount(8);
        cars[0].configureTransmission().setType("Automatic");

        cars[0].configureFuelSystem().setFuelType("Petrol");
        cars[0].configureFuelSystem().setTankCapacity(52);

        cars[0].configureBody().isConvertible(true);
        cars[0].configureBody().isSkyroofPresent(false);

        cars[0].configureFittings().setBonnetMaterial("Aluminium");
        cars[0].configureFittings().setExhaustType("Dual Rear Exit");



        cars[1] = new Car("Jeep", "Grand Cherokee SRT", "SUV", "Deep Cherry Red");
        
        cars[1].configureEngine().setType("HEMI");
        cars[1].configureEngine().setCylinderCount(8);
        cars[1].configureEngine().setDisplacement(2998);

        cars[1].configureTransmission().setSpeedCount(8);
        cars[1].configureTransmission().setType("Automatic");

        cars[1].configureFuelSystem().setFuelType("Petrol");
        cars[1].configureFuelSystem().setTankCapacity(93);

        cars[1].configureBody().isConvertible(false);
        cars[1].configureBody().isSkyroofPresent(true);

        cars[1].configureFittings().setBonnetMaterial("Aluminium");
        cars[1].configureFittings().setExhaustType("Dual Rear Exit");



        cars[2] = new Car("Rolls Royce", "Dawn", "Open Top", "Black Badge");
        
        cars[2].configureEngine().setType("V-type");
        cars[2].configureEngine().setCylinderCount(12);
        cars[2].configureEngine().setDisplacement(6598);

        cars[2].configureTransmission().setSpeedCount(8);
        cars[2].configureTransmission().setType("Automatic");

        cars[2].configureFuelSystem().setFuelType("Petrol");
        cars[2].configureFuelSystem().setTankCapacity(82);

        cars[2].configureBody().isConvertible(false);
        cars[2].configureBody().isSkyroofPresent(false);

        cars[2].configureFittings().setBonnetMaterial("Steel");
        cars[2].configureFittings().setExhaustType("Dual Rear Exit");



        cars[3] = new Car("Volvo", "XC90", "SUV", "Onyx Black");
        
        cars[3].configureEngine().setType("Twin Turbo Supercharged");
        cars[3].configureEngine().setCylinderCount(4);
        cars[3].configureEngine().setDisplacement(1969);

        cars[3].configureTransmission().setSpeedCount(8);
        cars[3].configureTransmission().setType("Automatic");

        cars[3].configureFuelSystem().setFuelType("Petrol");
        cars[3].configureFuelSystem().setTankCapacity(68);

        cars[3].configureBody().isConvertible(false);
        cars[3].configureBody().isSkyroofPresent(true);

        cars[3].configureFittings().setBonnetMaterial("Aluminium");
        cars[3].configureFittings().setExhaustType("Dual Rear Exit");
        cars[3].configureFittings().setExhaustType("Roof Fin Spoiler");



        cars[4] = new Car("Lamborghini", "Huracan", "Sports Car", "Arancio Borealis");
        
        cars[4].configureEngine().setType("V-type");
        cars[4].configureEngine().setCylinderCount(10);
        cars[4].configureEngine().setDisplacement(5204);

        cars[4].configureTransmission().setSpeedCount(7);
        cars[4].configureTransmission().setType("Automatic");

        cars[4].configureFuelSystem().setFuelType("Petrol");
        cars[4].configureFuelSystem().setTankCapacity(90);

        cars[4].configureBody().isConvertible(false);
        cars[4].configureBody().isSkyroofPresent(false);

        cars[4].configureFittings().setBonnetMaterial("Carbon Fibre");
        cars[4].configureFittings().setExhaustType("Dual Rear Double Exit");
        cars[4].configureFittings().setSpoilerType("Lighted Spoiler");



        for (int i = 0; i < 5; i++) {
            System.out.println("\fCar " + (i + 1) + ":\n======");
            cars[i].displayProperties();
        }
    }
}