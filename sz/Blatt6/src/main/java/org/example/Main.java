package org.example;

import java.util.List;

public class Main {

    public static void main(String[] args) {
        new Polynomial(List.of(6, -5, 1)).divide(new Polynomial(List.of(1, 1, 0, 1, 1, 0, 0, 0, 1)));
    }
}
