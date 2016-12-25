package threading;

/**
 * Created by aliziyaan on 11/10/16.
 */
public class Printer implements Runnable {

    String a;

    public Printer(String a){
        this.a = a;
    }

    @Override
    public void run() {
        for(int i = 0; i < 20; i ++){
            System.out.print(a);
            System.out.print(a.toUpperCase());
        }
    }
}
