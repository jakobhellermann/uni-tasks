package symmetricencryption.encoding;

public interface TextEncoding {
    int decodeChar(char c) throws InvalidEncodingException;
    char encodeChar(int value) throws InvalidEncodingException;
}
