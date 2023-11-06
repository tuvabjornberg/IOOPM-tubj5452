package org.ioopm.calculator;

import javax.naming.BinaryRefAddr;

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

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e, Environment vars) {
        SymbolicExpression r = e.eval(vars); 
        if (r.equals(expected)) {
            System.out.println("Passed: " + r);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + r + "'");
        }
    }

    public static void testsForEvaluating() {
        Environment vars = new Environment(); 
        SymbolicExpression a = new Addition(new Constant(5), new Constant(37)); 
        SymbolicExpression b = new Constant(42); 
        testEvaluating(b, a, vars);

        vars = new Environment(); 
        SymbolicExpression c = new Multiplication(new Addition(new Constant(3), new Constant(7)), new Constant(2));
        SymbolicExpression d = new Constant(20);
        testEvaluating(d, c, vars); 

        vars = new Environment(); 
        SymbolicExpression e = new Division(new Subtraction(new Constant(4), new Constant(2)), new Constant(2));
        SymbolicExpression f = new Constant(1);
        testEvaluating(f, e, vars); 

        vars = new Environment(); 
        SymbolicExpression g = new Negation(new Constant(8));
        SymbolicExpression h = new Constant(-8);
        testEvaluating(h, g, vars); 

        vars = new Environment(); 
        SymbolicExpression i = new Sin(new Constant(Math.PI/2));
        SymbolicExpression j = new Constant(1);
        testEvaluating(j, i, vars); 

        vars = new Environment(); 
        SymbolicExpression k = new Addition(new Multiplication(new Constant(2), new Constant(3)), new Sin(new Constant(0)));
        SymbolicExpression l = new Constant(6);
        testEvaluating(l, k, vars); 

        vars = new Environment(); 
        SymbolicExpression m = new Assignment(new Multiplication(new Constant(5), new Constant(2)), new Variable("x"));
        SymbolicExpression n = new Constant(10);
        testEvaluating(n, m, vars); 

        vars = new Environment(); 
        SymbolicExpression o = new Multiplication(new Addition(new Constant(5), new Variable("x")), new Constant(2)); 
        testEvaluating(o, o, vars);

        vars = new Environment(); 
        SymbolicExpression p = new Division(new Constant(10), new Constant(2)); 
        SymbolicExpression q = new Constant(5); 
        testEvaluating(q, p, vars);

        vars = new Environment(); 
        Variable v1 = new Variable("f"); 
        Variable v2 = new Variable("z"); 
        Constant c2 = new Constant(2); 
        Constant c3 = new Constant(3); 

        Assignment r = new Assignment(new Addition(v1, c2), v1); 
        testEvaluating(new Addition(v1, c2), r, vars); 
        Assignment s = new Assignment(c3, v2); 
        testEvaluating(c3, s, vars);
        testEvaluating(new Constant(5), new Addition(v2, c2), vars);

        vars = new Environment(); 
        Variable x = new Variable("x"); 
        Constant three = new Constant(3); 
        Assignment xEqualsThree = new Assignment(three, x); 
        testEvaluating(three, xEqualsThree, vars);

        Variable y = new Variable("y");
        testEvaluating(new Addition(three, y), new Addition(x, y), vars);

        Variable z = new Variable("z"); 
        Constant two = new Constant(2); 
        Assignment yEquals = new Assignment(new Addition(z, two), y); 
        testEvaluating(new Addition(z, two), yEquals, vars);

        Assignment zEqualsThree = new Assignment(three, z); 
        testEvaluating(three, zEqualsThree, vars);
        testEvaluating(new Addition(z, two), y, vars);

        Variable f1 = new Variable("f"); 
        Assignment fEquals = new Assignment(y, f1); 
        testEvaluating(new Addition(z, two), fEquals, vars);

        Constant six = new Constant(6); 
        testEvaluating(new Addition(new Addition(z, two), six), new Addition(f1, new Multiplication(z, two)), vars); 

        Variable g1 = new Variable("g"); 
        Assignment gEqualsZPlusX = new Assignment(new Addition(z, x), g1);
        testEvaluating(six, gEqualsZPlusX, vars);
        testEvaluating(six, g1, vars);
        testEvaluating(new Addition(z, two), f1, vars);
        testEvaluating(three, z, vars);
        testEvaluating(new Addition(new Addition(z, two), new Constant(9)), new Addition(f1, new Multiplication(z, z)), vars);
        
        vars = new Environment(); 
        SymbolicExpression v = new Multiplication(new Sin(new Constant(Math.PI/2)), new Constant(4)); 
        SymbolicExpression w = new Constant(4); 
        testEvaluating(w, v, vars);

        vars = new Environment(); 
        Variable x2 = new Variable("x"); 
        Assignment xEquals = new Assignment(new Constant(8), x2);
        testEvaluating(new Constant(26), new Multiplication(new Addition(new Constant(5), xEquals), two), vars);

        vars = new Environment(); 

        NamedConstant answer = new NamedConstant("Answer", 42); 
        SymbolicExpression life = new Constant(42); 
        testEvaluating(life, answer, vars);
        testEvaluating(new Constant(84), new Addition(answer, answer), vars); 
        
        Assignment invalid = new Assignment(new Constant(43), answer); 
        testEvaluating(new Constant(43), invalid, vars);
        //testEvaluating(new Constant(42), answer, vars);
    }

    public static void testsForVarsSingleton() {
        Vars v1 = Vars.instance();  
        Vars v2 = Vars.instance(); 

        assert v1 == v2 : "Vars instance not the same"; 

        System.out.println("Vars Singleton Test Passed");
    }

    private static void testsForQuitSingleton() {
        Quit quit1 = Quit.instance();
        Quit quit2 = Quit.instance();

        assert quit1 == quit2 : "Quit instances are not the same";

        System.out.println("Quit Singleton Test Passed");
    }
    
    public static void main(String[] args) {
        testsForPrinting();
        testsForEvaluating();
        testsForVarsSingleton(); 
        testsForQuitSingleton(); 
    }
}
