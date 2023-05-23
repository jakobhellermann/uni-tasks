package symmetricencryption;

import symmetricencryption.algorithm.Vigenere;
import symmetricencryption.encoding.InvalidEncodingException;
import symmetricencryption.encoding.TextEncoding;

import java.security.InvalidParameterException;

public abstract class SymmetricEncryption {
    protected TextEncoding keyEncoding;
    protected TextEncoding messageEncoding;

    protected SymmetricEncryption(TextEncoding keyEncoding, TextEncoding messageEncoding) {
        this.keyEncoding = keyEncoding;
        this.messageEncoding = messageEncoding;
    }

    public abstract String encrypt(String key, String message) throws InvalidEncodingException;

    public abstract String decrypt(String key, String ciphertext) throws InvalidEncodingException;

    public static SymmetricEncryption create(String algorithmName, TextEncoding keyEncoding, TextEncoding messageEncoding) {
        return switch (algorithmName) {
            case "vigenere" -> new Vigenere(keyEncoding, messageEncoding, 26);
            default -> throw new InvalidParameterException("unknown encryption algorithm: " + algorithmName);
        };
    }

    public static SymmetricEncryption create(String algorithmName, TextEncoding encoding) {
        return SymmetricEncryption.create(algorithmName, encoding, encoding);
    }
}
