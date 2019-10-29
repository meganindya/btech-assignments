package programs.q9.pack9;

//import programs.q9.SamePack;

public class DiffPack {
    public int val;
    
    public DiffPack(int val) {
        try {
            this.val = val;
            //val = new SamePack(val).val;        // new SamePack(val).val is inaccesible
        }

        catch(Exception e) {
            System.out.println("Variable not visible");
        }
    }
}