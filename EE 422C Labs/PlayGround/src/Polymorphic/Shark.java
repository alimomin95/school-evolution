package Polymorphic;

/**
 * Created by aliziyaan on 10/12/16.
 */
public class Shark extends Animals implements Carnivorous, Swim{

    public Shark(int age){
        super(age);
    }

    public String eatmeat(){
        return "Meat Meat";
    }
    public String swim(){
        return "Swim Swim Swim";
    }
    public String eat(){
        //System.out.println(super.eat());
        return "Fish as food";
    }
    public void printer(){
        System.out.print("Hello");
    }
}
