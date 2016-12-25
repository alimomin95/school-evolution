package serialize;

import java.io.Serializable;

/**
 * Created by aliziyaan on 11/27/16.
 */
public class ClientInfo implements Serializable {
    public String name;
    public Boolean online;

    public ClientInfo(String name, Boolean online){
        this.name = name;
        this.online = online;
    }
}
