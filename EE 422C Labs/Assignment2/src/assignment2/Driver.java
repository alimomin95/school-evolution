package assignment2;

/*  * EE422C Project 2 (Mastermind) submission by
 * <Ali Ziyaan Momin>
 * <AZM259>
 * Slip days used: <0>
 * Fall 2016
 */

import java.util.*;

public class Driver {
    public static void main (String[] args) {

        boolean testMode = false;

        for(String s: args) {
            if (s.equals("1")) {
                testMode = true;
            }
        }

        boolean reRun = true;
        while(reRun){
            Scanner console = new Scanner(System.in);
            Game G = new Game(testMode, console);
            reRun = G.runGame();
        }

    }
}
