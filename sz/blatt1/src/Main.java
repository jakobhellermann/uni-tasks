import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

public class Main {
    static int alphabetSize = 26;

    // maps a-z to 0-25
    static int decodeChar(char input) {
        return input - 'a';
    }

    // maps 0-25 to a-z
    static char encodeChar(int input) {
        return (char) ('a' + input);
    }


    static class Viginere {
        public static String encrypt(String key, String message) {
            StringBuilder builder = new StringBuilder(message.length());
            for (int i = 0; i < message.length(); i++) {
                int messageCode = decodeChar(message.charAt(i));
                int keyCode = decodeChar(key.charAt(i % key.length()));
                int newCode = (messageCode + keyCode) % alphabetSize;
                builder.append(encodeChar(newCode));
            }
            return builder.toString();

            /*return IntStream.range(0, message.length())
                    .mapToObj(i -> {
                        int messageCode = decodeChar(message.charAt(i));
                        int keyCode = decodeChar(key.charAt(i % key.length()));

                        int newCode = (messageCode + keyCode) % alphabetSize;
                        return String.valueOf(encodeChar(newCode));
                    })
                    .collect(Collectors.joining());*/
        }

        public static String decrypt(String key, String encrypted) {
            StringBuilder builder = new StringBuilder(encrypted.length());
            for (int i = 0; i < encrypted.length(); i++) {
                int messageCode = decodeChar(encrypted.charAt(i));
                int keyCode = decodeChar(key.charAt(i % key.length()));
                int newCode = Math.floorMod(messageCode - keyCode, alphabetSize);
                builder.append(encodeChar(newCode));
            }
            return builder.toString();
        }
    }

    public static void aufgabe1() {
        String message = "ichwillnichtmitihmtanzen";
        String key = "key";

        String encrypted = Viginere.encrypt(key, message);
        System.out.println(encrypted);

        String original = Viginere.decrypt(key, encrypted);
        System.out.println(original);
    }


    public static void aufgabe2() {
        String msg = """
                Ocs yif jcs Cvtirsfcv scvsf udscvsv bfivzesocoatsv
                Rif, jcs Oatstsfszijs tcsoo, jio scvzcks Deuid cv jsf
                Msjcvi, jio yistfsvj jsf kivzsv Viatx ebbsv yif. So
                yif mivatmid kivz dssf, mivatmid oioosv jfsc ejsf
                pcsf Dsgxs jifcv. Ysvv so irsf pedd yif, im
                tisgbckoxsv zycoatsv zysc gvj jfsc Gtf viatxo, tesfxs
                miv lsjso Yefx, jio jcs ivjsfsv Kisoxs oikxsv, gfj
                uim mcx lsjsm cvo Ksonfisat.""";

        // print histogram
        // msg.chars()
        //         .mapToObj(a -> (char) a)
        //         .filter(Character::isAlphabetic)
        //         .collect(Collectors.groupingBy(a -> a, Collectors.counting()))
        //         .entrySet()
        //         .stream()
        //         .sorted(Map.Entry.comparingByValue())
        //         .forEachOrdered(x -> {
        //             var a = (float) x.getValue() / msg.length();
        //             System.out.println(x.getKey() + ": " + a * 100);
        //         });

        HashMap<Character, Character> replacements = new HashMap<>();
        replacements.put('s', 'e');
        replacements.put('j', 'd');
        replacements.put('c', 'i');
        replacements.put('i', 'a');
        replacements.put('k', 'g');
        replacements.put('f', 'r');
        replacements.put('v', 'n');
        replacements.put('t', 'h');
        replacements.put('g', 'u');
        replacements.put('y', 'w');
        replacements.put('o', 's');
        replacements.put('r', 'b');
        replacements.put('a', 'c');
        replacements.put('x', 't');
        replacements.put('n', 'p');
        replacements.put('b', 'f');
        replacements.put('e', 'o');
        replacements.put('h', 'h');
        replacements.put('u', 'k');
        replacements.put('d', 'l');
        replacements.put('p', 'v');
        replacements.put('l', 'j');
        replacements.put('m', 'm');
        replacements.put('z', 'z');
        replacements.put('q', '?');
        replacements.put('w', '?');

        // missing mappings
        for (int i = 0; i < 25; i++) {
            char c = (char) ('a' + i);
            if (!replacements.containsKey(c)) System.out.println(c);
        }


        StringBuilder a = new StringBuilder(msg.length());
        for (int i = 0; i < msg.length(); i++) {
            char c = msg.charAt(i);
            if (replacements.containsKey(c)) {
                c = replacements.get(c);
            }
            if (Character.isUpperCase(c) && replacements.containsKey(Character.toLowerCase(c))) {
                c = Character.toUpperCase(replacements.get(Character.toLowerCase(c)));
            }
            a.append(c);
        }
        System.out.println(a.toString());


        /*for(int i = 0; i < 26; i++) {
            String shifted = Viginere.encrypt(String.valueOf((char)('a' + i)), msg);
            System.out.println(i);
            System.out.println(shifted);
        }*/

    }

    public static void main(String[] args) {
        aufgabe2();
    }
}