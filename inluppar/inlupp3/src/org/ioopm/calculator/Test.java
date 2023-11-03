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

    public static void testsForPrinting() {
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

        Addition a3 = new Addition(l2, l2);
        Multiplication m4 = new Multiplication(a3, c2); 
        testPrinting("(log (9.0 + y) + log (9.0 + y)) * 2.0", m4);
    }

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e) {
        SymbolicExpression r = e.eval(); 
        if (r.equals(expected)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void testsForEvaluating() {
        SymbolicExpression a = new Addition(new Constant(5), new Constant(37)); 
        SymbolicExpression b = new Constant(42); 
        testEvaluating(b, a);

        SymbolicExpression c = new Multiplication(new Addition(new Constant(3), new Constant(7)), new Constant(2));
        SymbolicExpression d = new Constant(20);
        testEvaluating(d, c); 

        SymbolicExpression e = new Division(new Subtraction(new Constant(4), new Constant(2)), new Constant(2));
        SymbolicExpression f = new Constant(1);
        testEvaluating(f, e); 

        SymbolicExpression g = new Negation(new Constant(8));
        SymbolicExpression h = new Constant(-8);
        testEvaluating(h, g); 

        SymbolicExpression i = new Sin(new Constant(Math.PI / 2));
        SymbolicExpression j = new Constant(1);
        testEvaluating(j, i); 

        SymbolicExpression k = new Addition(new Multiplication(new Constant(2), new Constant(3)), new Sin(new Constant(0)));
        SymbolicExpression l = new Constant(6);
        testEvaluating(l, k); 

        SymbolicExpression m = new Assignment(new Variable("x"), new Multiplication(new Constant(5), new Constant(2)));
        SymbolicExpression n = new Constant(10);
        testEvaluating(n, m); 

        SymbolicExpression o = new Multiplication(new Addition(new Constant(5), new Variable("x")), new Constant(2)); 
        testEvaluating(o, o);

        SymbolicExpression p = new Division(new Constant(10), new Constant(2)); 
        SymbolicExpression q = new Constant(5); 
        testEvaluating(q, p);

        Assignment r = new Assignment(new Variable("f"), new Addition(new Variable("z"), new Constant(2))); 
        Assignment s = new Assignment(new Variable("z"), new Constant(3)); 
        SymbolicExpression t = new Addition(r, new Multiplication(s, new Constant(2))); 
        SymbolicExpression u = new Addition(new Variable("y"), new Addition(new Constant(2), new Constant(6))); 
        testEvaluating(u, t);
        
        SymbolicExpression v = new Multiplication(new Sin(new Constant(1)), new Constant(4)); 
        SymbolicExpression w = new Constant(0); 
        testEvaluating(w, v);
    }
    
    public static void main(String[] args) {
        testsForPrinting();
        testsForEvaluating();
    }
}
