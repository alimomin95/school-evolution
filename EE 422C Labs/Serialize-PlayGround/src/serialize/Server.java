package serialize;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Observable;

/**
 * Created by aliziyaan on 11/27/16.
 */
public class Server extends Observable {
    public static void main(String[] args){
        try{
            new Server().setUpNetworking();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void setUpNetworking() throws Exception{
        ServerSocket serverSocket = new ServerSocket(5000);
        while(true){
            Socket clientSocket = serverSocket.accept();
            ClientObserver writer = new ClientObserver(clientSocket.getOutputStream());
            ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
            ClientInfo e = (ClientInfo) ois.readObject();
            System.out.println(e.name);
            Thread t = new Thread(new ClientHandler(clientSocket));
            t.start();
            addObserver(writer);
            System.out.println("got a connection");
        }
    }

    class ClientHandler implements Runnable{

        private BufferedReader reader;

        public ClientHandler(Socket clientSocket){
            Socket socket = clientSocket;
            try{
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            }catch (IOException e){
                e.printStackTrace();
            }
        }


        @Override
        public void run() {

            String message;

            try{
                while ((message = reader.readLine())!= null){
                    System.out.print("Server read: " + message);
                    setChanged();
                    notifyObservers(message);
                }
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }
}
