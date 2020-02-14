import java.io.*;
import java.net.*;


public class AckServer extends Thread
{
    private ServerSocket s;
    public AckServer(int port) throws IOException
    {
        s = new ServerSocket(port,5);
    }
    public void run()
    {
        System.out.println("Server Started....Listening");
        while(true)
        {
            try
            {
                Socket serv = s.accept();
                System.out.println("Connected to " + serv.getRemoteSocketAddress());
                DataInputStream in = new DataInputStream(serv.getInputStream());
                DataOutputStream out = new DataOutputStream(serv.getOutputStream());

                System.out.println(in.readUTF());
                out.writeUTF("Thank you for connecting to " + serv.getLocalSocketAddress()+ "\nGoodbye!");
                serv.close();
            }
            catch (IOException e) 
            {
                e.printStackTrace();
                break;
            } 
        }
    }
    public static void main(String [] args) 
    {
        int port = 12345;
        try 
        {
           Thread t = new AckServer(port);
           t.start();
        } 
        catch (IOException e) 
        {
           e.printStackTrace();
        }
    }
}
