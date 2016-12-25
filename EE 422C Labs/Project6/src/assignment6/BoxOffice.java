/*
 * Multithreading Theater.java
 * EE422C Project 6 submission by
 * Ali Ziyaan Momin
 * azm259
 * 16470
 * Slip days used: <1>
 * Fall 2016
 */

package assignment6;

import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

public class BoxOffice implements Runnable {

    private String boxOfficeID;
    private Theater theater;
    private int numOfClients;
    private Integer[] clients;
    private static int clientID = 1;
    private static ArrayList<String> reserved = new ArrayList<>();

    public BoxOffice(String boxOfficeID, Theater theater, int numOfClients){
        this.boxOfficeID = boxOfficeID;
        this.theater = theater;
        this.numOfClients = numOfClients;
        clients = new Integer[numOfClients + 1];
        fillClientList();

    }

    private void fillClientList(){
        for(int i = numOfClients; i > 0; i --){
            this.clients[i] = clientID;
            clientID ++;
        }
    }

    private static String a = "a";
    private static ReentrantLock lock = new ReentrantLock();
    private static boolean vaccant = false;

    @Override
    public void run() {
        Theater.Seat seat = new Theater.Seat(0,0);
        Theater.Ticket ticket = null;
        boolean flag = true;

        for (int i = numOfClients; i > 0; i--) {
            try {
                Thread.sleep(5);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized (a) {
                seat = theater.bestAvailableSeat();
                if (seat == null) {
                    break;
                }
                if(reserved.contains(seat.toString())){
                    i++;
                    flag = false;
                }
                else{
                    reserved.add(seat.toString());
                }
                //lock.lock();
            }
            synchronized (a){
                //lock.unlock();
                if(flag){
                    ticket = theater.printTicket(boxOfficeID, seat, clients[i]);
                    if(ticket == null){
                        i++;
                    }
                    try {
                        Thread.sleep(250);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
            flag = true;
        }
        synchronized (theater){
            if(!vaccant && seat == null){
                vaccant = true;
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("Sorry, we are sold out!");
            }
        }
    }
}
