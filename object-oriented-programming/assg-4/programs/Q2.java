package programs;

import static java.lang.System.*;

public class Q2 implements ErrorMsgs {
    public static void main(String args[]) {
        String str;
        int m = 0, n = 0;

        boolean erroneous = false;
        // lambda function for functional interface
        Error msg = (boolean e, String s) -> {
            if (!e)
                out.print("Error:");
            
            out.println("\t" + s);
        };

        try {
            if (args.length != 3)
                throw new Exception(err1);
            
            else {
                str = args[0];
                int length = str.length();
                
                try {
                    m = Integer.parseInt(args[1]);

                    if (m < 0 || m >= length)
                        throw new IllegalArgumentException(err4);
                }
                catch (Exception e) {
                    if (e instanceof NumberFormatException)
                        msg.getError(erroneous, err2);
                    else
                        msg.getError(erroneous, e.getMessage());
                    
                    erroneous = true;
                }

                try {
                    n = Integer.parseInt(args[2]);

                    if (n < 1 || n > length)
                        throw new IllegalArgumentException(err5);
                }
                catch (Exception e) {
                    if (e instanceof NumberFormatException)
                        msg.getError(erroneous, err3);
                    else
                        msg.getError(erroneous, e.getMessage());
                    
                    erroneous = true;
                }

                if (!erroneous && (m > n))
                    throw new Exception(err6);
                
                if (!erroneous && (m == n))
                    throw new Exception(err7);
            }
        }
        catch (Exception e) {
            msg.getError(erroneous, e.getMessage());
            return;
        }

        if (erroneous)  return;


        StringBuilder sb = new StringBuilder(str.substring(m, n));
        sb.reverse();
        out.println("Reversed substring: " + (new String(sb)));
    }
}


interface ErrorMsgs {
    public static final String err1 = "Invalid number of arguments";
    public static final String err2 = "Invalid lower index type";
    public static final String err3 = "Invalid upper index type";
    public static final String err4 = "Lower index out of range";
    public static final String err5 = "Upper index out of range";
    public static final String err6 = "Lower index higher than upper index";
    public static final String err7 = "Empty substring";
}

// functional interface
interface Error {
    public void getError(boolean e, String s);
}