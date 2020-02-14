import java.io.*;
import java.net.*;


public class TCPClient {
    public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String args[]) throws IOException {
        System.out.print("\033[H\033[2J");
        System.out.flush();

        final String serverAddr = "127.0.0.1";
        final int port = 4200;

        Socket conn = null;

        try {
            System.out.println("connecting to ''" + serverAddr + "' on port '" + port + "'");
            conn = new Socket(serverAddr, port);

            System.out.println("\n" + "connected to '" + conn.getRemoteSocketAddress().toString().substring(1) + "'\n");

            final DataOutputStream out = new DataOutputStream(conn.getOutputStream());
            final DataInputStream inp  = new DataInputStream(conn.getInputStream());

            chat(conn, inp, out);
        }

        catch (final IOException e) {
            e.printStackTrace();
        }

        finally {
            if (!conn.isClosed()) {
                System.out.println("\n" + "connection with '" + conn.getRemoteSocketAddress().toString().substring(1) + "' ended");
                conn.close();
            }
        }
    }

    public static void chat(Socket conn, DataInputStream inp, DataOutputStream out) throws IOException {
        String message = "";

        while (true) {
            System.out.print("Client: ");
            message = br.readLine();
            out.writeUTF(message);

            if (message.equalsIgnoreCase("bye"))
                break;

            message = inp.readUTF();
            System.out.print("Server: ");
            System.out.println(message);

            if (message.equalsIgnoreCase("bye"))
                break;
        }
    }
}
