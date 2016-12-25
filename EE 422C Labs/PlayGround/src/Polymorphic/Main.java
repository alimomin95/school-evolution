package Polymorphic;

/**
 * Created by aliziyaan on 8/28/16.
 */
import java.lang.reflect.Array;
import java.util.*;
public class Main {
    public static void main(String [] args) {
        /*Animals nemo = new Animals(10);
        System.out.println(nemo.getAge());
        System.out.println(((Shark)nemo).eat());
        */



        //Object obj = new Computer();
        //Computer cg = new Laptop();
        //Computer rh = new Desktop();
        //Desktop mh = new Laptop();
        //A variable = new B();

        ArrayList<Computer> lap = new ArrayList<>();
        lap.add(new Computer());
        lap.add(new Laptop());

        System.out.println(getSuperData(lap));

    }

    public static int getSuperData(ArrayList<? super Notebook> cunt){
        cunt.add(new Notebook());
        return ((Computer)cunt.get(0)).memory();
    }

    public static int getExtendData(ArrayList<? extends Computer> cunt){
        cunt.add(null);
        return ((Notebook)cunt.get(2)).memory();
    }
}
class Computer {
    public int memory() {
        return 20;
    }
    public boolean hasBattery() {
        return false;
    }
    public String toString() {
        return "s: " + memory();
    }
}

class Laptop extends Computer {
    public int memory() {
        return 100;
    }
    public boolean hasBattery() {return true; }
}

class Desktop extends Computer {
    public int memory() {
        return 10;
    }
    public String getName() {
        return "desk";
    }
}

class Notebook extends Laptop {
    public boolean rotate () {
        return true;
    }
}
