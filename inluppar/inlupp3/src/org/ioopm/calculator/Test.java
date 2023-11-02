package org.ioopm.calculator;

import org.ioopm.calculator.ast.*; 

public class Test {

    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }
    
    public static void main(String[] args) {
        Constant c1 = new Constant(5); 
        Constant c2 = new Constant(2); 
        Variable v1 = new Variable("x"); 
        Addition a1 = new Addition(c1, v1); 
        Multiplication m1 = new Multiplication(a1, c2); 

        testPrinting("(5 + x) * 2", m1); 

        Variable v2 = new Variable("y"); 
        Division d1 = new Division(m1, v2); 

        testPrinting("(5 + x) * 2 / y", d1);

        Constant c3 = new Constant(9);
        Constant c4 = new Constant(1); 
        Sin si = new Sin(c3); 
        Subtraction s = new Subtraction(c3, si); 
        Division d2 = new Division(c4, s); 
        Multiplication m2 = new Multiplication(d1, d2);

        testPrinting("(5 + x) * 2 / y * 1 / (9 - sin9)", m2);

        Addition a2 = new Addition(c3, v2); 
        Log l = new Log(a2);

        testPrinting("log(9 + y)", l);

        Exp e = new Exp(a2); 
        Multiplication m3 = new Multiplication(a2, e); 

        testPrinting("(9 + y) * e^(9 + y)", m3);
    }
}
