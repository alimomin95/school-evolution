package mtr;

/**
 * Created by aliziyaan on 10/12/16.
 */
public class MyException extends IllegalArgumentException {
    public MyException(){}
    public MyException(String message){
        super(message);
    }
}
