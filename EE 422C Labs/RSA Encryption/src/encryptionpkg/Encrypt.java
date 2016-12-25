package encryptionpkg;

/**
 * Created by aliziyaan on 12/20/16.
 */
public class Encrypt {
    static int N = (89)*(97);
    static int e = 101;

    public static int encryptThis(char M){
        int numericM = (int) M;

        return ((int) (Math.pow(numericM,e) % N));
    }
}
