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

import com.sun.jmx.remote.internal.ArrayQueue;

import java.util.ArrayList;
import java.util.List;

public class Theater {
	/*
	 * Represents a seat in the theater
	 * A1, A2, A3, ... B1, B2, B3 ...
	 */
	static class Seat {
		private int rowNum;
		private int seatNum;

		public Seat(int rowNum, int seatNum) {
			this.rowNum = rowNum;
			this.seatNum = seatNum;
		}

		public int getSeatNum() {
			return seatNum;
		}

		public int getRowNum() {
			return rowNum;
		}

		@Override
		public String toString() {
			String seatLabel = str(rowNum);
			String returnString = seatLabel + Integer.toString(seatNum);
			return returnString;
		}

		private static String str(int i) {
			return i < 0 ? "" : str((i / 26) - 1) + (char)(65 + i % 26);
		}
	}

  	/*
	 * Represents a ticket purchased by a client
	 */
	static class Ticket {
		private String show;
		private String boxOfficeId;
		private Seat seat;
	  	private int client;

		public Ticket(String show, String boxOfficeId, Seat seat, int client) {
			this.show = show;
			this.boxOfficeId = boxOfficeId;
			this.seat = seat;
			this.client = client;
		}

		public Seat getSeat() {
			return seat;
		}

		public String getShow() {
			return show;
		}

		public String getBoxOfficeId() {
			return boxOfficeId;
		}

		public int getClient() {
			return client;
		}

		@Override
		public String toString() {
			String pTicket = "-------------------------------\n" + "| Show: " + show + spacer(8 + show.length()) +
					"| Box Office ID: " + boxOfficeId + spacer(17 + boxOfficeId.length()) + "| Seat: " + seat.toString() +
					spacer(8 + seat.toString().length()) + "| Client: " + Integer.toString(client) + spacer(10 + Integer.toString(client).length())
					+ "-------------------------------\n";
			return pTicket;
		}

		public String spacer(int occupied){
			String returnString = "";
			for(int i = occupied; i < 30; i ++){
				returnString = returnString + " ";
			}
			returnString = returnString + "|\n";
			return returnString;
		}

	}

	private static int numRows;
	private static int seatsPerRow;
	private static String show;
	private static int numOfSeats;
	private static int numRemaining;
	private static int nextOpenSeat;
	private static List<Ticket> transactionLog;
	private static String a = "a";
	private static String b = "b";


	public Theater(int numRows, int seatsPerRow, String show) {
		this.numRows = numRows - 1;
		this.seatsPerRow = seatsPerRow;
		this.show = show;
		this.numOfSeats = numRows*seatsPerRow;
		this.numRemaining = numOfSeats;
		this.nextOpenSeat = 0;
		transactionLog = new ArrayQueue<>(numRows*seatsPerRow);
	}

	/*
	 * Calculates the best seat not yet reserved
	 *
 	 * @return the best seat or null if theater is full
   */
	public Seat bestAvailableSeat() {
		synchronized (this){
			if(nextOpenSeat >= numOfSeats){
				return null;
			}
			int seatNum = nextOpenSeat % seatsPerRow + 1;
			int rowNum = nextOpenSeat/ seatsPerRow;
			Seat returnSeat = new Seat(rowNum, seatNum);
			nextOpenSeat ++;
			return returnSeat;
		}
	}

	/*
	 * Prints a ticket for the client after they reserve a seat
   * Also prints the ticket to the console
	 *
   * @param seat a particular seat in the theater
   * @return a ticket or null if a box office failed to reserve the seat
   */
	public Ticket printTicket(String boxOfficeId, Seat seat, int client) {
		synchronized (b){
			Ticket ticket = new Ticket(this.show, boxOfficeId, seat, client);
			if(transactionLog.contains(ticket)){
				return null;
			}
			else{
				transactionLog.add(ticket);
				System.out.println(ticket);
			}
			return ticket;
		}

	}

	/*
	 * Lists all tickets sold for this theater in order of purchase
	 *
   * @return list of tickets sold
   */
	public List<Ticket> getTransactionLog() {
		return transactionLog;
	}
}
