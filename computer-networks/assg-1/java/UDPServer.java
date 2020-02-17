
import java.io.*;
import java.util.*;
import java.net.*;


public class UDPServer extends Thread {
    private DatagramSocket sock;

    public UDPServer(int port) throws IOException {
        sock = new DatagramSocket(port);
    }

    public void run() {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("server listening on port '" + sock.getLocalPort() + "'");

            try {
                chat(sock);
            }
            catch (Exception e) {
                e.printStackTrace();
                break;
            }

            System.out.print("\n" + "Exit? (Y/n): ");
            if (sc.nextLine().equalsIgnoreCase("Y"))
                break;
            else
                System.out.println();
        }
    }

    public static void chat(DatagramSocket sock) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String message = "";

        byte[] recvData = new byte[1024];
        byte[] sendData = new byte[1024];

        while (true) {
            DatagramPacket recvPack = new DatagramPacket(recvData, recvData.length);
            sock.receive(recvPack);
            InetAddress IPAddress = recvPack.getAddress();
            int port = recvPack.getPort();
            System.out.println("packet received from '" + IPAddress + ":" + port + "'");
            message = new String(recvPack.getData());
            System.out.print("MESSAGE : " + message);

            if (message.equalsIgnoreCase("bye"))
                break;

            System.out.print("REPLY   : ");
            message = br.readLine();
            sendData = message.getBytes();
            DatagramPacket sendPack = new DatagramPacket(sendData, sendData.length, IPAddress, port);
            sock.send(sendPack);

            if (message.equalsIgnoreCase("bye"))
                break;
        }
    }

    public static void main(String args[]) {
        System.out.print("\033[H\033[2J");
        System.out.flush();

        final int port = 4200;

        try {
            Thread t = new UDPServer(port);
            t.start();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
