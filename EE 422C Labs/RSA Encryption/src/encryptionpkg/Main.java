package encryptionpkg;

/**
 * Created by aliziyaan on 12/20/16.
 */
public class Main {
    public static void main(String[] args){
        char M = 'a';
        int C = Encrypt.encryptThis(M);
        char D = Decrypt.decryptThis(C);
        System.out.print(D);
    }
}
