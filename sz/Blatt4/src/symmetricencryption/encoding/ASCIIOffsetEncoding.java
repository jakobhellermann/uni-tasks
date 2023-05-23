package symmetricencryption.encoding;

public class ASCIIOffsetEncoding implements TextEncoding {
    char base;
    int nCharacters;

    public ASCIIOffsetEncoding(char base, int nCharacters) {
        this.base = base;
        this.nCharacters = nCharacters;
    }

    @Override
    public int decodeChar(char c) throws InvalidEncodingException {
        int code = c - this.base;
        if (code < 0 || code >= this.nCharacters) throw new InvalidEncodingException();
        return code;
    }

    @Override
    public char encodeChar(int value) throws InvalidEncodingException {
        if (value < 0 || value >= this.nCharacters) throw new InvalidEncodingException();
        return (char) (this.base + value);
    }
}
