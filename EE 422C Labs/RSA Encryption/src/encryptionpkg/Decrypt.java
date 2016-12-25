package encryptionpkg;

import java.math.BigInteger;

/**
 * Created by aliziyaan on 12/20/16.
 */
public class Decrypt {
    static int N = (89)*(97);
    static int d = 7277;

    public static char decryptThis(int C){
        BigInteger numericC = new BigInteger(Integer.toString(C));
        BigInteger power = numericC.pow(d);
        BigInteger result = power.mod(new BigInteger(Integer.toString(N)));
//        int numericM = ((int) Math.pow(C,d)) % N;
        return (char) result.intValue();
    }
}
