package org.ioopm.calculator;

import org.ioopm.calculator.ast.*; 

public class Test {

    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals(e.toString())) {//expected.equals("" + e)) {
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
        Log l1 = new Log(c1); 
        Assignment as = new Assignment(v1, c1);

        testPrinting("(5.0 + x) * 2.0", m1); 
        testPrinting("log 5.0", l1);
        testPrinting("x = 5.0", as);

        Variable v2 = new Variable("y"); 
        Division d1 = new Division(m1, v2); 

        testPrinting("(5.0 + x) * 2.0 / y", d1);

        Constant c3 = new Constant(9);
        Constant c4 = new Constant(1); 
        Sin si = new Sin(c3); 
        Subtraction s = new Subtraction(c3, si); 
        Division d2 = new Division(c4, s); 
        Multiplication m2 = new Multiplication(d1, d2);

        testPrinting("(5.0 + x) * 2.0 / y * 1.0 / (9.0 - sin 9.0)", m2);

        Addition a2 = new Addition(c3, v2); 
        Log l2 = new Log(a2);

        testPrinting("log (9.0 + y)", l2);

        Exp e = new Exp(a2); 
        Multiplication m3 = new Multiplication(a2, e); 

        testPrinting("(9.0 + y) * e^ (9.0 + y)", m3);
    }
}
