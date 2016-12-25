package serialize;

import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Observable;
import java.util.Observer;

/**
 * Created by aliziyaan on 11/27/16.
 */
public class ClientObserver extends PrintWriter implements Observer {

    public ClientObserver(OutputStream out){
        super(out);
    }

    @Override
    public void update(Observable o, Object arg) {
        this.println(arg);
        this.flush();
    }
}
