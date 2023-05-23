public class Main {
    public static void main(String[] args) {
        int a = DES.lookupSbox(1, (byte) 0b100111);
        int b = DES.lookupSbox(3, (byte) 0b011001);
        int c = DES.lookupSbox(5, (byte) 0b110011);
        int d = DES.lookupSbox(7, (byte) 0b000111);
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
        System.out.println(d);
    }
}