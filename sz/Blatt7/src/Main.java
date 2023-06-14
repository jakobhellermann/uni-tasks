import java.math.BigInteger;
import java.util.function.Supplier;

public class Main {
    public static void main(String[] args) {
        BigInteger e = BigInteger.valueOf(65537);
        BigInteger p = new BigInteger("eb628434bcc2b89bafb2fe3e64a932dc8be90c11e954589c1120c938882ee8bba786be21787305a9bcb63c9f7ac3c2838f0c8458acfc2b62e7cbf8c1598a6d8c0d9e343662e37e37aefbe49b3fce5caafb36f03aa154fd996f15d6cec4e8f8f163182ff7c533eb40140e36861cf38e592e45127e3e02a284fcf956b0d84efc6d000ecd9b6d089f122a84725478e2cf86fce5170960c9ce838a2d71703e4ba6bcdf4e303fff1fb1e8236e02484e87f1da1857a8dabdeb5eb045673b1a06c1ff08c5c21271a432c35c6c9b38137102d9929311903afbd1ae0573e72b4b381eb6bd154236073eaa422bc98be4f141bb722a51b68a287a896bf53a79c43646842eff", 16);
        BigInteger q = new BigInteger("ceb052c9732614fee3c0a197a5ae0fcd83422243918ab83bc678656ae0344232a7c1070b7d5aabaae2bda96bf590da4830238b606f24b29626f1bfa00cce39f5f9bb9c1c3ead98f2055e373abf01e1fe1c816e12e0ed13791461c435123dad8cbe80e474f753aa9d115a8b93c167adceaee5a18ceedef88d307427fc495d9e44d4268ba83c4a65c4667b7df79f342639da3ddd2777926848855ca0068668efe7f27d65f455074c960bbc168bfb3a1225cd6f42585ddba6b3484f36707524133b81dd01d062591fec1b756766aeebe667bf9e2480eebb5964bc5eaff4b165e142772ce64b229a7258667a3964f08e06dfbfe3e3c1cf918395b89c1fdb18907711", 16);

        RSA.PublicKey publicKey = new RSA.PublicKey(p.multiply(q), e);
        RSA.PrivateKey privateKey = new RSA.PrivateKey(p, q, e);

        BigInteger testMessage = BigInteger.valueOf(1234);
        BigInteger testMessageEncrypted = RSA.encrypt(publicKey, testMessage);

        double durationRoundtrip = timeMs(() -> RSA.decrypt(privateKey, publicKey, RSA.encrypt(publicKey, testMessage)));
        double durationEncrypt = timeMs(() -> RSA.encrypt(publicKey, testMessage));
        double durationDecrypt = timeMs(() -> RSA.decrypt(privateKey, publicKey, testMessageEncrypted));

        System.out.printf("%.2f ms roundtrip\n", durationRoundtrip);
        System.out.printf("%.2f ms encrypt\n", durationEncrypt);
        System.out.printf("%.2f ms decrypt\n", durationDecrypt);
    }

    static double timeMs(Supplier<?> f) {
        for(int i = 0; i < 15;i++) f.get();

        long start = System.nanoTime();
        f.get();
        long end = System.nanoTime();

        return (end - start) / 1000.0 / 1000.0;
    }
}