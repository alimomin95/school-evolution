package quiz5;


import java.util.Arrays;

class SudokuBoard {
    int[][] board;
    boolean[][] initial;
    int SIZE;
    int N;

    public SudokuBoard(int size) {
        this.SIZE = size;
        N = (int) (Math.sqrt(SIZE) + 1e-3);
        board = new int[SIZE][SIZE];
    }

    public SudokuBoard(int size, int[][] starting) {
        this(size);
        initial = new boolean[SIZE][SIZE];
        // Is a square is initialized? If not, program may change its value.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (starting[i][j] != 0)
                    initial[i][j] = true;
            }
        }

        for (int row = 0; row < SIZE; row++) {
            board[row] = Arrays.copyOf(starting[row], SIZE);
        }
    }

    /**
     * Given a square, find the next one that was not initialized.
     */
    public int nextEmpty(int n) {
        n++;
        if (n == SIZE * SIZE)
            return n;
        int r = n / SIZE;
        int c = n % SIZE;
        while (initial[r][c]) {
            n++;
            r = n / SIZE;
            c = n % SIZE;
            if (n == SIZE * SIZE)
                return n;
        }
        return n;
    }

    /**
     * Whether safe to place number 'a' in space 'n'.
     */
    public boolean isSafe(int a, int n) {
        // TODO fill here
        int row = n/SIZE;
        int col = n%SIZE;
        if (!UsedInRow(row, a) && !UsedInColumn(col, a) && !UsedInBox(row - row % (int)Math.sqrt(SIZE), col - col % (int)Math.sqrt(SIZE), a)) {
            return true;
        }
        return false;
    }

    public void print() {
        for (int r = 0; r < SIZE; r++) {
            String blank = "";
            for (int c = 0; c < SIZE; c++) {
                if (board[r][c] == 0)
                    System.out.print(blank + "*");
                else
                    System.out.print(blank + board[r][c]);
                blank = " ";
            }
            System.out.println();
        }
    }

    // check if n not in particular row
    private boolean UsedInRow(int row, int n) {
        for (int i = 0; i < SIZE; i++) {
            if (board[row][i] == n) {
                return true;
            }
        }
        return false;
    }

    // check if n not in particular column
    private boolean UsedInColumn(int col, int n) {
        for (int i = 0; i < SIZE; i++) {
            if (board[i][col] == n) {
                return true;
            }
        }
        return false;
    }

    // check if n not in particular box
    private boolean UsedInBox(int boxStartRow, int boxStartCol, int n) {
        for (int i = 0; i < Math.sqrt(SIZE); i++) {
            for (int j = 0; j < Math.sqrt(SIZE); j++) {
                if (board[i + boxStartRow][j + boxStartCol] == n) {
                    return true;
                }
            }
        }
        return false;
    }
}
