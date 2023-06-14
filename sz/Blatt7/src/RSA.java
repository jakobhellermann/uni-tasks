import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class RSA {
    static class PublicKey {
        public final BigInteger n;
        public final BigInteger e;

        PublicKey(BigInteger n, BigInteger e) {
            this.n = n;
            this.e = e;
        }
    }

    static class PrivateKey {
        public BigInteger n;
        public BigInteger d;


        // gcd(e, phi(n)) == 0
        public PrivateKey(BigInteger p, BigInteger q, BigInteger e) {
            BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));

            this.n = p.multiply(q);
            this.d = e.modInverse(phi);
        }
    }

    public static BigInteger encrypt(PublicKey publicKey, BigInteger message) {
        return message.modPow(publicKey.e, publicKey.n);
    }

    public static BigInteger decrypt(PrivateKey privateKey, PublicKey publicKey, BigInteger encrypted) {
        return encrypted.modPow(privateKey.d, publicKey.n);
    }


    public static String encrypt(PublicKey publicKey, String message) {
        Base64.Encoder encoder = Base64.getEncoder();
        StringBuilder result = new StringBuilder();

        int chunkSize = 256;

        byte[] messageBytes = message.getBytes(StandardCharsets.UTF_8);
        int nChunks = (message.length() + chunkSize - 1) / chunkSize;
        for (int i = 0; i < nChunks; i += chunkSize) {
            BigInteger chunk = BigInteger.ZERO;

            for (int c = 0; i + c < message.length(); c++) {
                chunk = chunk.or(BigInteger.valueOf(messageBytes[i + c]).shiftLeft(8 * c));
            }

            BigInteger value = RSA.encrypt(publicKey, chunk);
            System.out.println(encoder.encodeToString(value.toByteArray()).length());
            result.append(encoder.encodeToString(value.toByteArray()));
        }

        return result.toString();
    }

    public static String decrypt(PrivateKey privateKey, PublicKey publicKey, String encrypted) {
        Base64.Decoder decoder = Base64.getDecoder();
        System.out.println(encrypted.length());

        int base64BlockLength = 684;


        StringBuilder result = new StringBuilder();

        for (int blockIndex = 0; blockIndex < encrypted.length() / base64BlockLength; blockIndex++) {
            byte[] values = decoder.decode(encrypted.substring(blockIndex, blockIndex + base64BlockLength));
            BigInteger value = new BigInteger(values);

            BigInteger original = RSA.decrypt(privateKey, publicKey, value);

            int chunkSize = 256;

            for (int c = 0; c < chunkSize; c++) {
                int singleByte = original.shiftRight(c).and(BigInteger.valueOf(0b11111111)).intValueExact();
                result.append((char)(singleByte));
            }
        }

        return result.toString();
    }
}

