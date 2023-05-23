package symmetricencryption.algorithm;

import symmetricencryption.SymmetricEncryption;
import symmetricencryption.encoding.InvalidEncodingException;
import symmetricencryption.encoding.TextEncoding;

public class Vigenere extends SymmetricEncryption {
    int alphabetSize;

    public Vigenere(TextEncoding keyEncoding, TextEncoding valueEncoding, int alphabetSize) {
        super(keyEncoding, valueEncoding);
        this.alphabetSize = alphabetSize;
    }


    @Override
    public String encrypt(String key, String message) throws InvalidEncodingException {
        StringBuilder builder = new StringBuilder(message.length());
        for (int i = 0; i < message.length(); i++) {
            int messageCode = this.messageEncoding.decodeChar(message.charAt(i));
            int keyCode = this.keyEncoding.decodeChar(key.charAt(i % key.length()));
            int newCode = (messageCode + keyCode) % alphabetSize;
            builder.append(this.messageEncoding.encodeChar(newCode));
        }
        return builder.toString();
    }

    @Override
    public String decrypt(String key, String ciphertext) throws InvalidEncodingException {
        StringBuilder builder = new StringBuilder(ciphertext.length());
        for (int i = 0; i < ciphertext.length(); i++) {
            int messageCode = this.messageEncoding.decodeChar(ciphertext.charAt(i));
            int keyCode = this.keyEncoding.decodeChar(key.charAt(i % key.length()));
            int newCode = Math.floorMod(messageCode - keyCode, alphabetSize);
            builder.append(this.messageEncoding.encodeChar(newCode));
        }
        return builder.toString();
    }
}
