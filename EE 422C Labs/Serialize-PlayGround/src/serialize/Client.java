package serialize;


import java.io.*;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by aliziyaan on 11/27/16.
 */
public class Client {

    private static BufferedReader reader;
    private static PrintWriter writer;
    private String name;
    private Boolean online;
    private ClientInfo clientInfo;

    public Client(){
        name = "ali";
        online = true;
        clientInfo = new ClientInfo(name, online);
    }

    public static void main(String[] args){
        try{
            new Client().run();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void setUpNetworking() throws Exception {
        Socket socket = new Socket("127.0.0.1", 5000);
        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        writer = new PrintWriter(socket.getOutputStream());
        ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
        oos.writeObject(clientInfo);
        oos.flush();
        System.out.println("Networking established with " + socket.getInetAddress().getHostAddress());
        System.out.println(writer);
        Thread readerThread = new Thread(new IncomingReader());
        Thread writerThread = new Thread(new MessageWriter());
        readerThread.start();
        writerThread.start();
    }


    class IncomingReader implements Runnable{

        @Override
        public void run() {
            String message;
            try{
                while((message = reader.readLine()) != null){
                    System.out.println(message);
                }
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }

    class MessageWriter implements Runnable{

        @Override
        public void run() {
            //System.out.print("User: ");
            Scanner sc = new Scanner(System.in);
            while(true) {
                if(sc.hasNextLine()){
                    writer.println(sc.nextLine());
                    writer.flush();
                    //System.out.print("User: ");
                }
            }
        }
    }


    public void run() throws Exception {
        setUpNetworking();
    }
}
