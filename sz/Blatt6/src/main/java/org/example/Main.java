package org.example;

import java.util.List;

public class Main {

    public static void main(String[] args) {
        Polynomial m = new Polynomial(List.of(1, 1, 0, 1, 1, 0, 0, 0, 1));
        Polynomial p = new Polynomial(List.of(1, 1));
        Polynomial[] results = m.divide(p);

        System.out.println("result: " + results[0]);
        System.out.println("remainder: " + results[1]);
    }
}
