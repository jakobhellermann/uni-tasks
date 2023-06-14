package org.example;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Polynomial {
    // c0 x^0 + c1 x^1 + c2 x^2 + ...
    private final List<Integer> coefficients;

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = coefficients;
    }

    // coefficient * x^degree
    static Polynomial ofDegree(int degree, int coefficient) {
        List<Integer> coefficients = new ArrayList<>(Collections.nCopies(degree + 1, 0));
        coefficients.set(coefficients.size() - 1, coefficient);
        return new Polynomial(coefficients);
    }

    // multiply with coefficient * x^degree
    Polynomial mul(int degree, int coefficient) {
        ArrayList<Integer> newCoefficients = new ArrayList<>(this.coefficients);
        newCoefficients.addAll(0, Collections.nCopies(degree, 0));
        newCoefficients.replaceAll(integer -> integer * coefficient);

        return new Polynomial(newCoefficients);
    }

    Polynomial sub(Polynomial other) {
        int maxDegree = Math.max(this.degree(), other.degree());
        Polynomial newPolynomial = new Polynomial(new ArrayList<>(Collections.nCopies(maxDegree + 1, 0)));
        for (int i = 0; i <= maxDegree; i++) {
            newPolynomial.coefficients.set(i, this.getCoefficient(i) - other.getCoefficient(i));
        }

        while (!newPolynomial.coefficients.isEmpty() && newPolynomial.highestCoefficient() == 0) {
            newPolynomial.coefficients.remove(newPolynomial.coefficients.size() - 1);
        }

        return newPolynomial;
    }

    public Polynomial[] divide(Polynomial divisor) {
        if (divisor.isZero()) throw new IllegalArgumentException("divisor is zero");
        if (divisor.degree() > this.degree())
            throw new IllegalArgumentException("divisor has higher degree than dividend");

        System.out.println(this + " : " + divisor);

        Polynomial quotient = new Polynomial(new ArrayList<>());
        Polynomial remain = this;

        while (divisor.degree() <= remain.degree() && !remain.isZero()) {
            int degreeDifference = remain.degree() - divisor.degree();
            int factor = remain.highestCoefficient() / divisor.highestCoefficient();

            Polynomial step = divisor.mul(degreeDifference, factor);
            System.out.println(step);
            System.out.println("------------------");
            remain = remain.sub(step);
            System.out.println(remain);

            quotient.setCoefficient(degreeDifference, factor);
        }

        System.out.println("remainder: '" + remain + "'");

        return new Polynomial[]{quotient, remain};
    }


    private int degree() {
        return coefficients.size() - 1;
    }

    private int highestCoefficient() {
        return this.coefficients.isEmpty() ? 0 : coefficients.get(coefficients.size() - 1);
    }

    private int getCoefficient(int i) {
        return this.coefficients.size() > i ? this.coefficients.get(i) : 0;
    }

    private void setCoefficient(int i, int coefficient) {
        while (this.coefficients.size() <= i) {
            this.coefficients.add(0);
        }

        this.coefficients.set(i, coefficient);
    }

    private boolean isZero() {
        return this.highestCoefficient() == 0;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            int coefficient = coefficients.get(i);

            if (coefficient == 0) continue;

            s.append(coefficient);
            if (i != 0) {
                s.append("x^");
                s.append(i);
            }

            if (i != 0 && coefficients.subList(0, i).stream().anyMatch(c -> c != 0)) {
                s.append(" + ");
            }
        }
        return s.toString();
    }
}