package mtr;

/**
 * Created by aliziyaan on 10/12/16.
 */
import java.util.*;

public class Main {


    public static void main(String[] args){
        /*
        tryCatchBlock();
        throwExceptions(1);
        Scanner sc = new Scanner(System.in);
        readingUserInput(sc);

        //WordBank wB = new WordBank();
        //wB.doStuff();

        Foo x = new Foo();
        Bar y = new Bar();
        Foo z = y;

        z.fred();


        Scanner sc = new Scanner(System.in);

        boolean done = false;
        while(!done){
            try{
                int n = sc.nextInt();
                done = isPerfectSquare(n);
                if(done){
                    System.out.println("Is a perfect square");
                }
                else System.out.println("Not a perfect square");
            }catch (IllegalArgumentException e1){
                e1.printStackTrace();
            }
        }


        ArrayList<String> listH = new ArrayList<String>();
        listH.add(0, "Q");
        listH.add("P");
        listH.add(0, "K");
        listH.add(1, "P");
        listH.add("X");
        listH.remove(2);
        System.out.println(listH);
        */

        int[] dataa = {2,3};
        stuff(dataa);
        System.out.println(Arrays.toString(dataa));

        if(5<6 || (4/0)==0){
            System.out.println("haha");
        }

        Scanner s = new Scanner("/src");



    }

    public static void stuff(int[] vals){
        vals[vals.length -1] += 3;
        vals = new int[2];
        vals[0] ++;
    }

    public static boolean isPerfectSquare(int n){
        if (n<0) throw new IllegalArgumentException();
        return Math.sqrt(n)*Math.sqrt(n) == n;
    }

    private static void readingUserInput(Scanner sc){
        int a = sc.nextInt();
        double b = sc.nextDouble();
        System.out.println(a+b);
    }

    private static void throwExceptions(int amnt){
        if(amnt < 0){
            throw new MyException();
        }
        System.out.println("Amnt deposited");
    }

    private static void tryCatchBlock(){
        int a = 6;
        int b = 0;
        int[] x = {1,2,3,4,5};
        try{
            System.out.println(a/b);
            int i = 0;
            while(true){
                System.out.println(x[i]);
                i ++;
            }

        }catch(ArithmeticException e2){
            System.out.println("I don't know what the fuck is going on!");

        }catch(ArrayIndexOutOfBoundsException e3){
            System.out.println("Out of bounds caught");
        }
        finally{
            System.out.println("Final");
        }
        System.out.println("Outside");
    }

}

class WordBank {
    private HashSet<String> wordBank = new HashSet<String>();

    public void doStuff(){
        wordBank.add("hello");
        wordBank.add("world");
        wordBank.add("shit");
        wordBank.add("more shit");
        System.out.println(wordBank);
    }
}

class Foo {
    int x;
    public Foo (){
        x = 13;
    }
    public void doit(){
        System.out.println("Base");
    }
    public void fred(){
        System.out.println(x);
    }
}

class Bar extends Foo {
    int x;
    public Bar(){
        x = 14;
    }
    public void doit(){
        System.out.println("Derived");
    }
}
