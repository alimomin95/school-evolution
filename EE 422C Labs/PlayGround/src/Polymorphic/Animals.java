package Polymorphic;

/**
 * Created by aliziyaan on 10/12/16.
 */
public class Animals {
    int age;

    public Animals(int age){
        this.age = age;
    }

    public String eat(){
        return "food";
    }

    public int getAge(){
        return age;
    }
}
