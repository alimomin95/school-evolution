package assignment2;

/*  * EE422C Project 2 (Mastermind) submission by
 * <Ali Ziyaan Momin>
 * <AZM259>
 * Slip days used: <0>
 * Fall 2016
 */

import java.util.*;

public class Input {

    private int blackPegs;
    private int whitePegs;
    private boolean validity;
    private boolean win;

    public Input(){
        blackPegs = 0;
        whitePegs = 0;
        win = false;
    }

    public int getBlackPegs(){
        return blackPegs;
    }

    public int getWhitePegs(){
        return whitePegs;
    }

    public boolean getWin(){
        return win;
    }

    public static String getInput(Scanner console){
        return console.nextLine();
    }

    public boolean checkInput(String code, String guess){
        blackPegs = 0;
        whitePegs = 0;

        if(guess.equals(code)){
            validity = true;
            win = true;
            return validity;
        }

        if(guess.length() > code.length() || guess.length() != GameConfiguration.pegNumber){
            validity = false;
            win = false;
            return validity;
        }

        int colorsLength = GameConfiguration.colors.length;
        for(int i = 0; i < guess.length(); i++) {
            for(int j = 0; j < colorsLength; j ++){
                if(guess.charAt(i) == GameConfiguration.colors[j].charAt(0)){
                    validity = true;
                    break;
                }
                validity = false;
            }
        }

        if(!validity){
            win = false;
            return validity;
        }

        char[] codeChar = new char[code.length()];
        for(int i = 0; i < code.length(); i++){
            codeChar[i] = code.charAt(i);
        }

        char[] guessChar = new char[code.length()];
        for(int i = 0; i < code.length(); i++){
            guessChar[i] = guess.charAt(i);
        }

        for(int i = 0; i < code.length(); i++){
            if(codeChar[i] == guessChar[i]){
                codeChar[i] = '-';
                guessChar[i] = '-';
                blackPegs++;
            }
        }

        for(int i = 0; i < code.length(); i++){
            for(int j = 0; j < code.length(); j++){
                if(guessChar[j] == codeChar[i] && guessChar[j] != '-' && codeChar[i] != '-'){
                    guessChar[j] = '-';
                    codeChar[i] = '-';
                    whitePegs++;
                }
            }
        }

        validity = true;
        win = false;
        return validity;
    }
}
