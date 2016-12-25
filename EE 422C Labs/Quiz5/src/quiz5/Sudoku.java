package quiz5;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

/**
 * This is a Sudoku Solver that solves a partial Sudoku Board using recursion.
 * The Sudoku solver fills a N×N (N=9 by default) grid with digits so that each
 * column, each row, and each of the Size ×Size (N=Size × Size while Size =3 by
 * default) subgrids contains all of the digits from 1 to 9.
 * <p>
 * You need to implement the solve(SudokuBoard b, int current) method using
 * recursion and the isSafe(int a, int n) method that is used in the solve()
 * method.
 * </p>
 * <p>
 * Don't change other given methods/fields. You can add some private helper
 * methods but you may not add new public methods or fields.
 * </p>
 */
public class Sudoku {

    public static int noSolves = 0;
    public static int SIZE;

    @SuppressWarnings("resource")
    public static void main(String[] args) throws FileNotFoundException {

        // Initialize board
        Scanner sc = new Scanner(new File("sudoku.in"));

        boolean more = true;
        while (more) {
            int n = sc.nextInt();
            SIZE = n * n;
            int[][] initial = new int[SIZE][SIZE];

            for (int cell = 0; cell < SIZE * SIZE; cell++) {
                initial[cell / SIZE][cell % SIZE] = sc.nextInt();
            }
            solve(initial);
            more = sc.hasNextInt();
            if (more)
                System.out.println(); // Print blank line between testcases

        }
    }

    public static void solve(int[][] initial) {
        if (SIZE == 1) {
            System.out.println(1);
            return;
        }
        SudokuBoard brd = new SudokuBoard(SIZE, initial);
        if (solve(brd, brd.nextEmpty(-1)))
            brd.print();
        else
            System.out.println("NO SOLUTION");
    }

    public static boolean solve(SudokuBoard b, int current) {
        // TODO fill here using recursion
        // current increases from 0 to size^2 -1 -- first along a row, then
        // downwards.
        // IF the current placement is at square size^2, we are done.
        // ELSE
        // LOOP try out all 'size' numbers in the current square.
        // IF any number is safe to place there
        // Place it.
        // Call solve with the next square without an initial value.
        // IF above returns TRUE
        // RETURN TRUE.
        // ELSE
        // Remove the placement, (and try the next possible digit)
        // END LOOP
        // RETURN false (if we fall out of the LOOP without returning true, we
        // have exhausted 1-SIZE)
        //
        if(current == SIZE*SIZE){
            return true;
        }

        for(int i = 1; i <= SIZE; i++){
            if(b.isSafe(i, current)){
                b.board[current/SIZE][current%SIZE] = i;
                if(solve(b, b.nextEmpty(current))){
                    return true;
                }
                else{
                    b.board[current/SIZE][current%SIZE] = 0;
                }
            }
        }

        return false;
    }
}
