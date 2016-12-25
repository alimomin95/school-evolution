package assignment2;

/*  * EE422C Project 2 (Mastermind) submission by
 * <Ali Ziyaan Momin>
 * <AZM259>
 * Slip days used: <0>
 * Fall 2016
 */

import java.util.*;

public class Game {

    private Scanner console;
    private String code;
    private boolean debugMode;
    private int guessNumber;

    public Game (boolean B,Scanner C){
        console = C;
        debugMode = B;
        code = SecretCodeGenerator.getInstance().getNewSecretCode();
        guessNumber = GameConfiguration.guessNumber;
    }


    public boolean runGame(){
        String input = Print.printIntro(console).toUpperCase();
        while(true) {
            if (input.equals("Y")) {
                break;
            }

            else if(input.equals("N")){
                System.out.println("See you again!");
                return false;
            }

            else{
                input = Print.printSIntro(console).toUpperCase();
            }
        }

        System.out.println("\n\nGenerating secret code ....\n\n");

        Print printobj = new Print();
        while(guessNumber > 0){
            if(debugMode){
                Print.printCode(code);
            }

            Print.printBoard(guessNumber);
            String guess = Input.getInput(console);
            if(guess.equals("HISTORY")){
                printobj.printHistory();
                continue;
            }

            Input inputobj = new Input();
            if(inputobj.checkInput(code, guess)){
                if(inputobj.getWin()){
                    Print.printResult((Integer.toString(GameConfiguration.pegNumber)) +" black pegs – You win!!", guess);
                    break;
                }
                String result = printobj.resultString(inputobj.getBlackPegs(), inputobj.getWhitePegs(), guess);
                Print.printResult(result, guess);
                guessNumber--;
            }
            else{
                Print.printResult("INVALID INPUT", guess);
            }
        }

        if(guessNumber < 1){
            System.out.println("Sorry, you are out of guesses. You lose, boo-hoo.");
        }
        while(true) {
            System.out.print("\n\n\nDo you want to play again (Y/N)? ");
            String again = console.next().toUpperCase();
            if (again.equals("Y")) {
                return true;
            } else if (again.equals("N")) {
                return false;
            }
            else{
                System.out.print("Please enter Y/N! Do you want to play again? ");
            }
        }

    }
}
