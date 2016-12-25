package assignment2;

/*  * EE422C Project 2 (Mastermind) submission by
 * <Ali Ziyaan Momin>
 * <AZM259>
 * Slip days used: <0>
 * Fall 2016
 */

import java.util.*;

public class Print {

    private ArrayList<String> history = new ArrayList<>();
    public static String printIntro (Scanner console) {
        System.out.print("Welcome to Mastermind.  Here are the rules.\n" +
                " \n" +
                "This is a text version of the classic board game Mastermind.\n" +
                "The computer will think of a secret code. The code consists of " + Integer.toString(GameConfiguration.pegNumber) + " colored pegs.\n" +
                "The pegs MUST be one of six colors: blue, green, orange, purple, red, or yellow. A color may appear more than once in the code. You try to guess what colored pegs are in the code and what order they are in. After you make a valid guess the result (feedback) will be displayed.\n" +
                "The result consists of a black peg for each peg you have guessed exactly correct (color and position) in your guess. For each peg in the guess that is the correct color, but is out of position, you get a white peg. For each peg that is fully incorrect, you get no feedback.\n" +
                "Only the first letter of the color is displayed. B for Blue, R for Red, and so forth.\n" +
                "When entering guesses you only need to enter the first character of each color as a capital letter.\n" +
                " \n" +
                "You have " + Integer.toString(GameConfiguration.guessNumber) + " guesses to figure out the secret code or you lose the game. Are you ready to play? (Y/N): ");
        String in = console.nextLine();

        return in;
    }

    public static String printSIntro (Scanner console) {
        System.out.println("Please enter (Y?N): ");
        return console.nextLine();
    }

    public static void printCode(String code){
        System.out.println("Code: " + code + "\n");
    }

    public static void printBoard(int guessNumber){
        if(guessNumber > 1) {
            System.out.print("You have " + guessNumber + " guesses left.\n" + "What is your next guess?\n" + "Type in the characters for your guess and press enter.\n" + "Enter guess: ");
        }
        else{
            System.out.print("You have " + guessNumber + " guess left.\n" + "What is your next guess?\n" + "Type in the characters for your guess and press enter.\n" + "Enter guess: ");
        }
    }
    public static void printResult(String result, String guess){
        System.out.println(guess + "  -> Result: " + result +"\n");
    }

    public String resultString(int blackPegs, int whitePegs, String guess){
        if(blackPegs > 1 && whitePegs == 0){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(blackPegs) + " black pegs");
        }
        else if(blackPegs == 0 && whitePegs > 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(whitePegs) + " white pegs");
        }
        else if(blackPegs == 1 && whitePegs == 0){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return ("1 black peg");
        }
        else if(blackPegs == 0 && whitePegs == 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return ("1 white peg");
        }
        else if(blackPegs > 1 && whitePegs > 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(blackPegs) + " black pegs, " + Integer.toString(whitePegs) + " white pegs");
        }
        else if(blackPegs == 1 && whitePegs == 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(blackPegs) + " black peg, " + Integer.toString(whitePegs) + " white peg");
        }
        else if(blackPegs > 1 && whitePegs == 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(blackPegs) + " black pegs, " + Integer.toString(whitePegs) + " white peg");
        }
        else if(blackPegs == 1 && whitePegs > 1){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return (Integer.toString(blackPegs) + " black peg, " + Integer.toString(whitePegs) + " white pegs");
        }
        else if(blackPegs == 0 && whitePegs == 0){
            history.add((guess + "\t\t" + Integer.toString(blackPegs) + "B_" + Integer.toString(whitePegs) + "W"));
            return ("no pegs");
        }
        return "";
    }

    public void printHistory(){
        //System.out.println("\n");
        for(int i = 0; i < history.size(); i++){
            System.out.println(history.get(i));
        }
        System.out.println("\n");
    }
}
