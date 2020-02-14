import java.net.*;
import java.io.*;

public class Client 
{
   public static void main(final String [] args) throws IOException 
   {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        final String serverName = "127.0.0.1";
        final int port = 12345;
        try 
        {
            System.out.println("Connecting to " + serverName + " on port " + port);
            final Socket client = new Socket(serverName, port);
         
            System.out.println("Connected to " + client.getRemoteSocketAddress());

            final OutputStream outToServer = client.getOutputStream();
            final DataOutputStream out = new DataOutputStream(outToServer);
            final InputStream inFromServer = client.getInputStream();
            final DataInputStream in = new DataInputStream(inFromServer);

            out.writeUTF("Hello from " + client.getLocalSocketAddress());
            System.out.println("Server says " + in.readUTF());
            String inp = "";
            while(inp.compareTo("exit")!=0)
            {
                inp = br.readLine();
                
            }
         
            
            client.close();
        } 
        catch (final IOException e) 
        {
            e.printStackTrace();
        }
   }
}