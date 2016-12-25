package threading;

/**
 * Created by aliziyaan on 11/10/16.
 */
public class Main {

    public static void main(String[] args){
        Runnable a = new Printer("a");
        Runnable b = new Printer("b");
        Runnable c = new Printer("c");

        Thread t1 = new Thread(a);
        Thread t2 = new Thread(b);
        Thread t3 = new Thread(c);

        t1.start();
        t2.start();
        t3.start();
    }

}
