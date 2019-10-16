import bin.*;
import static java.lang.System.*;

class Treadmill {
    private static int q = 1;
    private static String arg[] = {};
        
    public static void main(String args[]) {
        if(args.length != 0) {
            try {
                q = Integer.parseInt(args[0]);
            }
            catch(NumberFormatException e) {
                out.println("Invalid Argument: " + e);
            }
            
            if(!(q >= 1 && q <= 11)) {
                out.println("Defaulting to Q1");
                q = 1;
            }

            if(args.length > 1) {
                arg = new String[args.length - 1];
                for(int i = 0; i < arg.length; i++)
                    arg[i] = args[i + 1];
            }
        }

        try {
            switch(q) {
                case 1:
                    Q1.main(arg);
                    break;
                case 2:
                    Q2.main(arg);
                    break;
                case 3:
                    Q3.main(arg);
                    break;
                case 4:
                    Q4.main(arg);
                    break;
                case 5:
                    Q5.main(arg);
                    break;
                case 6:
                    Q6.main(arg);
                    break;
                case 7:
                    Q7.main(arg);
                    break;
                case 8:
                    Q8.main(arg);
                    break;
                case 9:
                    Q9.main(arg);
                    break;
                case 10:
                    Q10.main(arg);
                    break;
                case 11:
                    Q11.main(arg);
                    break;
            }
        }
        catch(Exception e) {
            out.printf("Can't run Question %d due to %s\n", q, e);
        }
    }
}