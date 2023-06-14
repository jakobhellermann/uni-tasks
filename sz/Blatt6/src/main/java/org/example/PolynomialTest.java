package org.example;

import org.junit.Test;

import java.util.Arrays;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThrows;

/**
 * Test class for the polynomial class.
 */
public class PolynomialTest {

    /**
     * Tests the divide method with a normal case.
     */
    @Test
    public void testDivide() {
        Polynomial p1 = new Polynomial(Arrays.asList(6, -5, 1)); // 6 - 5x + x^2
        Polynomial p2 = new Polynomial(Arrays.asList(3, -1)); // 3 - x
        Polynomial[] result = p1.divide(p2);

        assertEquals("-1x^1 + 2", result[0].toString());
        assertEquals("", result[1].toString());
    }

    /**
     * Tests the divide method with the zero polynomial as divisor.
     */
    @Test
    public void testDivideByZeroPolynomial() {
        Polynomial p1 = new Polynomial(Arrays.asList(6, -5, 1)); // 6 - 5x + x^2
        Polynomial p2 = new Polynomial(Arrays.asList(0, 0)); // 0

        assertThrows(IllegalArgumentException.class, () -> {
            Polynomial[] result = p1.divide(p2);
        });
    }

    /**
     * Tests the divide method with a divisor whose degree is greater than that of the dividend.
     */
    @Test
    public void testDivideWhenDividendDegreeIsLessThanDivisor() {
        Polynomial p1 = new Polynomial(Arrays.asList(3, -1)); // 3 - x
        Polynomial p2 = new Polynomial(Arrays.asList(6, -5, 1)); // 6 - 5x + x^2

        assertThrows(IllegalArgumentException.class, () -> {
            Polynomial[] result = p1.divide(p2);
        });
    }

    /**
     * Tests the toString method.
     */
    @Test
    public void testDivideWithRemainder() {
        Polynomial p1 = new Polynomial(Arrays.asList(0, 0, -12, 1)); // 0 + 0x -12x^2 + x^3
        Polynomial p2 = new Polynomial(Arrays.asList(-10, 1)); // -10 + x
        Polynomial[] result = p1.divide(p2);

        assertEquals("1x^2 + -2x^1 + -20", result[0].toString()); // Quotient
        assertEquals("-200", result[1].toString()); // Rest
    }

    /**
     * Tests the divide method when a remainder is expected.
     */
    @Test
    public void testToString() {
        Polynomial p = new Polynomial(Arrays.asList(6, -5, 1)); // 6 - 5x + x^2
        assertEquals("1x^2 + -5x^1 + 6", p.toString());
    }

}
