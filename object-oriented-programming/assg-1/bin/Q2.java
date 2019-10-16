// Meganindya@Mega328p

package bin;

public class Q2 {
	public static void main(String args[]) {
		Car car1 = new Car("Hatchback",
							"Glowing Red",
							"Mini John Cooper Hardtop",
							(double) 3000000,
							"Manual 6-speed",
							17.12);
		Car car2 = new Car("Sedan",
							"Ionic Silver",
							"BMW Vision i8 Roadster",
							(double) 21400000,
							"Automatic Planetary 6-speed",
							47.62);
		
		car1.display();
		car2.display();
	}
}

class Car {
	private String type;
	private String colour;
	private String make;
	private Double price;
	private String gear_type;
	private Double mileage;
	
	Car(String type, String colour, String make,
		Double price, String gear_type, Double mileage) {
		this.type		= type;
		this.colour		= colour;
		this.make		= make;
		this.price		= price;
		this.gear_type	= gear_type;
		this.mileage	= mileage;
	}
	
	public void display() {
		System.out.println();
		System.out.println("Type"		+ "\t\t: " + type);
		System.out.println("Colour"		+ "\t\t: " + colour);
		System.out.println("Make"		+ "\t\t: " + make);
		System.out.println("Price"		+ "\t\t: " + price);
		System.out.println("Gear Type"	+ "\t: "   + gear_type);
		System.out.println("Mileage"	+ "\t\t: " + mileage);
		System.out.println();
	}
}
