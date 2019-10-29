package programs;

import java.io.*;

public class Q5 {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        for (int i = 0; i < 10; i++) {
            System.out.print("\fEnter string: ");
            try {
                String s = br.readLine();

                if (s.length() == 0)
                    throw new NullPointerException("Error: Empty string\n");
                else
                    System.out.println(s + " entered");
            }
            catch (NullPointerException e) {
                System.out.println(e.getMessage());
                return;
            }
        }
    }
}