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

import java.util.*;
import java.lang.Thread;

public class BookingClient {

    private String[] boxOffice;
    private static Integer[] clients;
    private static Theater theater;

    public static void main(String[] args){

        Map<String, Integer> box = new HashMap<>();
        box.put("BX1", 4000);
        box.put("BX2", 3);
        box.put("BX3", 4);
        box.put("BX4", 2);
        box.put("BX5", 1);
        box.put("Fifth", 2);

        Theater theat = new Theater(300, 5, "Ouija");
        BookingClient book = new BookingClient(box, theat);
        book.simulate();


    }

  /*
   * @param office maps box office id to number of customers in line
   * @param theater the theater where the show is playing
   */
    public BookingClient(Map<String, Integer> office, Theater theater) {
        this.theater = theater;
        this.boxOffice = new String[office.size()];
        this.clients = new Integer[office.size()];

        int i = 0;
        for(String key: office.keySet()){
            this.boxOffice[i] = key;
            this.clients[i] = office.get(key);
            i++;
        }
    }

  /*
   * Starts the box office simulation by creating (and starting) threads
   * for each box office to sell tickets for the given theater
   *
   * @return list of threads used in the simulation,
   *         should have as many threads as there are box offices
   */
	public List<Thread> simulate() {
        List<Thread> threads = new ArrayList<>();
        for(int i = 0; i < boxOffice.length; i++){
            Thread thread = new Thread(new BoxOffice(boxOffice[i], theater, clients[i]));
            thread.start();
            threads.add(thread);
        }
        return threads;
	}
}
