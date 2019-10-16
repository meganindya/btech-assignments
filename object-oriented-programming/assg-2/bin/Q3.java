package bin;

import static java.lang.System.*;

public class Q3 {
    public static void main(String args[]) {
        if(args.length == 0) {
            out.println("No Arguments");
            exit(0);
        }

        if(!new Q3().checkArgs(args)) {
            out.println("Invalid Arguments");
            exit(0);
        }

        out.println("All Clear");
    }

    boolean checkArgs(String args[]) {
        for(String s : args) {
            if(!Character.isUpperCase(s.charAt(0)))
                return false;
        }

        return true;
    }
}