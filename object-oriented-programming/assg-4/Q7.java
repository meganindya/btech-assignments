import static java.lang.System.*;
import java.util.*;

class Q7 {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        Student ob[] = new Student[20];
        ob[0] = new Student("Aakash", "Commerce", 11, 4);
        ob[1] = new Student("Soumitra", "Science", 12, 2);
        ob[2] = new Student("Sourish", "Science", 12, 3);
        ob[3] = new Student("Sagnik", "Science", 11, 1);
        ob[4] = new Student("Porsia", "Humanities", 11, 3);
        ob[5] = new Student("Shubhayan", "Humanities", 11, 1);
        ob[6] = new Student("Divyani", "Commerce", 12, 1);
        ob[7] = new Student("Abhirup", "Commerce", 11, 1);
        ob[8] = new Student("Kinjal", "Science", 11, 2);
        ob[9] = new Student("Ron", "Science", 11, 1);
        ob[10] = new Student("Aditya", "Science", 11, 4);
        ob[11] = new Student("Bishwaroop", "Commerce", 12, 3);
        ob[12] = new Student("Parthiv", "Science", 12, 1);
        ob[13] = new Student("Bishal", "Humanities", 11, 2);
        ob[14] = new Student("Sagar", "Humanities", 12, 3);
        ob[15] = new Student("Debal", "Commerce", 12, 2);
        ob[16] = new Student("Shalini", "Commerce", 11, 3);
        ob[17] = new Student("Aditya", "Humanities", 12, 1);
        ob[18] = new Student("Bandhuli", "Humanities", 12, 2);
        ob[19] = new Student("Debesh", "Commerce", 11, 2);

        while (true) {
            out.print("\fEnter credentials (Y/n): ");
            if (sc.next().charAt(0) != 'Y')   break;

            String name, branch; int classNo, rollNo;
            Student temp;
            
            try {
                out.print("Name: ");
                name = (sc.next() + sc.nextLine()).toLowerCase();

                out.print("Branch: ");
                branch = (sc.next() + sc.nextLine()).toLowerCase();

                out.print("Class: ");
                classNo = sc.nextInt();

                out.print("Roll No: ");
                rollNo = sc.nextInt();

                temp = new Student(name, branch, classNo, rollNo);
            }
            catch (Exception e) {
                out.println("\nError: Invalid Credentials");
                continue;
            }


            try {
                boolean found = false;
                for (Student i : ob) {
                    if (i.compareTo(temp) == 0) {
                        found = true;
                        break;
                    }
                }

                if (!found)
                    throw new Exception("Error: Student not found");
                else
                    out.println("\nStudent found");
            }
            catch (Exception e) {
                out.println("\n" + e.getMessage());
            }
        }

        sc.close();
    }
}


class Student implements Comparable<Student> {
    private String name;
    private String branch;
    private int classNo;
    private int rollNo;

    Student(String name, String branch, int classNo, int rollNo) {
        this.name = name.toLowerCase();
        this.branch = branch.toLowerCase();
        this.classNo = classNo;
        this.rollNo = rollNo;
    }

    public int compareTo(Student ob) {
        //out.println(ob.name + "|" + this.name +  "|" + ob.branch + "|" + this.branch + "|" + ob.classNo + "|" + this.classNo + "|" + ob.rollNo + "|" + this.rollNo);
        if (ob.name.equals(this.name) &&
            ob.branch.equals(this.branch) &&
            ob.classNo == this.classNo &&
            ob.rollNo == this.rollNo)
            return 0;
        else
            return 1;
    }
}