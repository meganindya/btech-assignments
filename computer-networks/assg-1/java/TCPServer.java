import java.io.*;
import java.util.*;
import java.net.*;


public class TCPServer extends Thread {
    private ServerSocket sock;
    private BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public TCPServer(int port) throws IOException {
        sock = new ServerSocket(port);
    }

    public void run() {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("server listening on port '" + sock.getLocalPort() + "'");
            Socket conn = null;

            try {
                conn = sock.accept();
                System.out.println("\n" + "server connected to '" + conn.getRemoteSocketAddress().toString().substring(1) + "'\n");
                DataInputStream inp  = new DataInputStream(conn.getInputStream());
                DataOutputStream out = new DataOutputStream(conn.getOutputStream());

                chat(conn, inp, out);

                System.out.print("\n" + "Exit? (Y/n): ");
                if (sc.nextLine().equalsIgnoreCase("Y"))
                    break;
                else
                    System.out.println();
            }

            catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }

        sc.close();
    }

    public void chat(Socket conn, DataInputStream inp, DataOutputStream out) throws IOException {
        String message = "";

        while (true) {
            message = inp.readUTF();
            System.out.print("Client: ");
            System.out.println(message);

            if (message.equalsIgnoreCase("bye")) {
                System.out.println("\n" + "connection with '" + conn.getRemoteSocketAddress().toString().substring(1) + "' ended");
                conn.close();
                break;
            }

            System.out.print("Server: ");
            message = br.readLine();
            out.writeUTF(message);

            if (message.equalsIgnoreCase("bye")) {
                System.out.println("\n" + "connection with '" + conn.getRemoteSocketAddress().toString().substring(1) + "' ended");
                conn.close();
                break;
            }
        }
    }

    public static void main(String args[]) {
        System.out.print("\033[H\033[2J");
        System.out.flush();

        final int port = 4200;

        try {
            Thread t = new TCPServer(port);
            t.start();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
