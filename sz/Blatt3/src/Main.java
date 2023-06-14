public class Main {

    static int multiplicativeInverseMod26(int value) {
        for (int i = 0; i < 26; i++) {
            if ((value * i) % 26 == 1) {
                return i;
            }
        }

        throw new RuntimeException("no inverse found");
    }

    record Vec2(int a, int b) {
        Vec2 mod(int modulus) {
            return new Vec2(Math.floorMod(a, modulus), Math.floorMod(b, modulus));
        }
    }

    record Matrix2x2(int a, int b, int c, int d) {
        Matrix2x2 invert() {
            int determinant = a * d - b * c;
            int inverse = multiplicativeInverseMod26(determinant);

            return new Matrix2x2(inverse * d, inverse * -b, inverse * -c, inverse * a);
        }

        Matrix2x2 mod(int modulus) {
            return new Matrix2x2(Math.floorMod(a, modulus), Math.floorMod(b, modulus), Math.floorMod(c, modulus), Math.floorMod(d, modulus));
        }

        Vec2 mul(Vec2 vec) {
            return new Vec2(this.a * vec.a + this.b * vec.b, this.c * vec.a + this.d * vec.b);
        }
    }

    static String decryptHill2(String text, Matrix2x2 key) {
        Matrix2x2 inverse = key.invert().mod(26);

        StringBuilder builder = new StringBuilder(text.length());
        for (int i = 0; i < text.length(); i += 2) {
            int code1 = text.charAt(i) - 'A';
            int code2 = text.charAt(i + 1) - 'A';

            Vec2 vec = new Vec2(code1, code2);
            Vec2 decrypted = inverse.mul(vec).mod(26);

            builder.append((char) ('A' + decrypted.a));
            builder.append((char) ('A' + decrypted.b));
        }

        return builder.toString();
    }
    static String encryptHill2(String text, Matrix2x2 key) {
        StringBuilder builder = new StringBuilder(text.length());
        for (int i = 0; i < text.length(); i += 2) {
            int code1 = text.charAt(i) - 'A';
            int code2 = text.charAt(i + 1) - 'A';

            Vec2 vec = new Vec2(code1, code2);
            Vec2 decrypted = key.mul(vec).mod(26);

            builder.append((char) ('A' + decrypted.a));
            builder.append((char) ('A' + decrypted.b));
        }

        return builder.toString();
    }


    public static void main(String[] args) {
        Matrix2x2 key = new Matrix2x2(6, 3, 5, 3);
        String text = """
                KSEXZZGHETHFXTCKJWFRWDEBKTNQKTGUQNIECCQYYQIPYLDWL
                HUCJRZZFVSYKKGUSFRNKTGOTACCRZCUVOCKPIXTLHFRPDBNLH
                NNSTTPDJMGHXPPWDFSYOESXECUVOWSKXHHSPLTCUVOROJBPJA
                NHFIIGOLHKSEXZZGHETHFXTCKJWHHUCAKCCEWCPCUVOGFMVCC
                RJMZYLPILHANGUSFZRIPJWLHCVVELHEBIRWSJRLHKEODGJLHK
                SXQPPWDJBMUYJIRCCQYKTCUCVGOHFCGVEAWETHFSPNVIALHYF
                CUPFDJTNXTWQEMZNLHKEODGJKGTCBXMBHFSRWSPCWLGOIPUII
                HKRJWMRKXWSJRWSYLWQVIDJEBDMKRSYLHTQVVKTMZMVGGVOAW
                CDMZCIYHNDHZBTFFYOESIPATWSCPWDLUCDANCVAEHQXTMRJWX
                TICKEFSYQHFLHKSEXXTHXPPIPCPSZQOQMXTYQQYIVJWKSXQIA
                GOMBHFINAJHFWLSFLH""".replaceAll("\n", "");

        String result = decryptHill2(text, key);
        System.out.println(result);

        String reencrypted = encryptHill2(text, key);
        System.out.println(reencrypted);
    }
}