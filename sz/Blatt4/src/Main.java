import symmetricencryption.SymmetricEncryption;
import symmetricencryption.encoding.InvalidEncodingException;
import symmetricencryption.encoding.LowercaseLatinEncoding;
import symmetricencryption.encoding.TextEncoding;

public class Main {
    public static void main(String[] args) throws InvalidEncodingException {
        TextEncoding encoding = new LowercaseLatinEncoding();
        SymmetricEncryption algorithm = SymmetricEncryption.create("vigenere", encoding);

        String encoded = algorithm.encrypt("key", "ichwillnicht");
        System.out.println(encoded);
        String decoded = algorithm.decrypt("key", encoded);
        System.out.println(decoded);
    }
}