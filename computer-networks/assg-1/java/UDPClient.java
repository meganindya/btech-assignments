import java.io.*;
import java.net.*;


class UDPClient {
    public static void main(String args[]) throws IOException {
        System.out.print("\033[H\033[2J");
        System.out.flush();

        DatagramSocket clientSocket = new DatagramSocket();

        chat(clientSocket);

        clientSocket.close();
    }

    public static void chat(DatagramSocket sock) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String message = "";

        byte[] recvData = new byte[1024];
        byte[] sendData = new byte[1024];

        InetAddress IPAddress = InetAddress.getByName("localhost");
        final int port = 4200;

        while (true) {
            System.out.print("MESSAGE : ");
            message = br.readLine();
            sendData = message.getBytes();
            DatagramPacket sendPack = new DatagramPacket(sendData, sendData.length, IPAddress, port);
            sock.send(sendPack);

            if (message.equalsIgnoreCase("bye"))
                break;

            DatagramPacket recvPack = new DatagramPacket(recvData, recvData.length);
            sock.receive(recvPack);
            InetAddress servAddr = recvPack.getAddress();
            int servPort = recvPack.getPort();
            System.out.println("packet received from '" + servAddr + ":" + servPort + "'");
            message = new String(recvPack.getData());
            System.out.print("REPLY   : " + message);

            if (message.equalsIgnoreCase("bye"))
                break;
        }
    }
}
