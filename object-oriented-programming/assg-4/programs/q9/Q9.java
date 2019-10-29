package programs.q9;

import static java.lang.System.*;
import programs.q9.pack9.*;

public class Q9 {
    public static void main(String args[]) {
        out.println(new SamePack(5).val);           // in same package as Q9 (programs.q9 package)

        out.println(new SamePackSub(10).val);       // in same package as Q9 and extends SamePack

        out.println(new DiffPack(15).val);          // in package programs.q9.pack9

        out.println(new DiffPackSub(20).val);       // in same package as DiffPack and extends programs.q9.SamePack
    }
}