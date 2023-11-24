package org.ioopm.calculator.tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.ast.*; 
import org.ioopm.calculator.visitor.*; 

public class AstTests {
    private ScopeStack stack; 
    private EvaluationVisitor evaluator; 

    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
        stack = new ScopeStack(new Environment()); 
        evaluator = new EvaluationVisitor(); 
    }

    @Test
    void additionTest() {
        Addition a1 = new Addition(new Constant(1), new Constant(6)); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            a1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator";
        String actualMessage1 = exception1.getMessage();
    
        assertTrue(actualMessage1.contains(expectedMessage1));

        assertFalse(a1.isConstant()); 
        assertFalse(a1.isCommand()); 
        assertTrue(a1.getName().contains("+"));
        assertEquals(50, a1.getPriority());

        assertEquals("1.0 + 6.0", a1.toString()); 

        SymbolicExpression aEval = evaluator.evaluate(a1, stack);  
        assertTrue(aEval.equals(new Constant(7))); 

        assertThrows(RuntimeException.class, () -> {
            Addition a2 = new Addition(null, null);
            evaluator.evaluate(a2, stack); 
        });

        Addition a3 = new Addition(new Constant(3), new Constant(5));
        Constant c1 = new Constant(8);
        assertNotEquals(a3, c1);
    }

    @Test
    void assignmentTest() {
        Assignment a1 = new Assignment(new Constant(3), new Variable("x")); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            a1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator";
        String actualMessage1 = exception1.getMessage();
        assertTrue(actualMessage1.contains(expectedMessage1));
       
        assertFalse(a1.isConstant()); 
        assertFalse(a1.isCommand()); 
        assertTrue(a1.getName().contains("="));
        assertEquals(0, a1.getPriority());

        assertEquals("3.0 = x", a1.toString()); 

        SymbolicExpression a1Eval = evaluator.evaluate(a1, stack); 
        assertTrue(a1Eval.equals(new Constant(3)));
        assertEquals(new Constant(3), stack.get(new Variable("x")));

        Assignment a2 = new Assignment(new Subtraction(new Variable("y"), new Division(new Cos(new Constant(0)), new Subtraction(new Constant(2), new Constant(1)))), new Variable("x")); 
        assertEquals("y - cos 0.0 / (2.0 - 1.0) = x", a2.toString()); 

        SymbolicExpression a2Eval = evaluator.evaluate(a2, stack); 
        assertTrue(a2Eval.equals(new Subtraction(new Variable("y"), new Constant(1))));

        assertThrows(RuntimeException.class, () -> {
            Assignment a3 = new Assignment(null, null);
            evaluator.evaluate(a3, stack); 
        });

        Assignment a4 = new Assignment(new Variable("a"), new Constant(5));
        Constant c1 = new Constant(5);    
        assertNotEquals(a4, c1);
    }
    
    @Test
    void atomTest() {
        Atom a1 = new Constant(4); 
        Atom a2 = new Variable("x"); 

        assertTrue(a1.isConstant());
        assertFalse(a2.isConstant());

        assertFalse(a1.isCommand());
        assertFalse(a2.isCommand());

        assertThrows(RuntimeException.class, () -> {
            a1.getName(); 
            a2.getName(); 

            a1.getValue(); 
            a2.getValue(); 

            a1.getVariable(); 
            a2.getVariable(); 
        });

        assertEquals(evaluator.evaluate(a1, stack).toString(), "4.0");
        assertEquals(evaluator.evaluate(a2, stack), a2);
    }

    @Test
    void binaryTest() {
        Binary b1 = new Addition(new Variable("x"), new Constant(3));
        assertEquals("x + 3.0", b1.toString());
        assertEquals(b1.getLhs(), new Variable("x")); 
        assertEquals(b1.getRhs(), new Constant(3)); 

        assertFalse(b1.isCommand());
        assertFalse(b1.isConstant());

        Binary b2 = new Addition(new Variable("a"), new Constant(5));
        Binary b3 = new Addition(new Variable("a"), new Constant(5));
        assertTrue(b2.equals(b3));
 
        Binary b4 = new Addition(new Variable("b"), new Constant(2));
        Binary b5 = new Multiplication(new Variable("b"), new Constant(2));
        assertFalse(b4.equals(b5));
    
        assertThrows(RuntimeException.class, () -> {
            b1.getName(); 
            b1.getValue(); 
            b1.getVariable();  
        });

        assertEquals(evaluator.evaluate(b5, stack) , b5);
    }

    @Test
    void clearTest() {
        Clear c1 = Clear.instance();  
        Clear c2 = Clear.instance(); 
        assertEquals(c1, c2);
        assertTrue(c1.equals(c2));

        assertEquals(c1.getName(), "clear");
        assertTrue(c1.isCommand());
        assertFalse(c1.isConstant());
        assertEquals(c1.getPriority(), 100);

        assertThrows(RuntimeException.class, () -> {
            c1.getValue(); 
            c1.getVariable(); 
            evaluator.evaluate(c1, stack); 
        });

        Vars v = Vars.instance(); 
        assertNotEquals(c1, v);
        assertNotEquals(c2, v);
    }

    @Test
    void commandTest() {
        Command c1 = Clear.instance(); 

        assertTrue(c1.isCommand());
        assertFalse(c1.isConstant());

        assertThrows(RuntimeException.class, () -> {
            c1.getValue(); 
            c1.getVariable(); 
            evaluator.evaluate(c1, stack);  
            c1.getName(); 
        });
    }

    @Test
    void constantTest() {
        Constant c1 = new Constant(6); 

        assertEquals(c1.getValue(), 6);
        assertTrue(c1.isConstant()); 
        assertFalse(c1.isCommand()); 
        assertEquals(100, c1.getPriority());

        Exception exception = assertThrows(RuntimeException.class, () -> {
            c1.getName(); 
        });
    
        String expectedMessage = "getName() called on expression with no name"; 
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));

        assertEquals("6.0", c1.toString()); 

        SymbolicExpression c1Eval = evaluator.evaluate(c1, stack);  
        assertTrue(c1Eval.equals(new Constant(6)));
    }

    @Test
    void cosTest() {        
        Cos c1 = new Cos(new Constant(0)); 

        Exception exception = assertThrows(RuntimeException.class, () -> {
            c1.getValue(); 
        });
    
        String expectedMessage = "getValue() called on expression with no operator";
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));        
        
        assertFalse(c1.isConstant()); 
        assertFalse(c1.isCommand()); 
        assertEquals(100, c1.getPriority());
        assertTrue(c1.getName().contains("cos"));

        assertEquals("cos 0.0", c1.toString()); 

        SymbolicExpression c1Eval = evaluator.evaluate(c1, stack); 
        assertTrue(c1Eval.equals(new Constant(1)));

        Addition c2 = new Addition(new Cos(new Multiplication(new Addition(new Constant(3), new Variable("r")), new Variable("u"))), new Constant(4)); 
        assertEquals("cos ((3.0 + r) * u) + 4.0", c2.toString()); 

        Assignment a1 = new Assignment(new Negation(new Constant(3)), new Variable("r")); 
        evaluator.evaluate(a1, stack); 
        Assignment a2 = new Assignment(new Constant(1), new Variable("u")); 
        evaluator.evaluate(a2, stack); 
        
        SymbolicExpression c2Eval = evaluator.evaluate(c2, stack); 
        assertEquals("5.0", c2Eval.toString()); 

        assertTrue(c2Eval.equals(new Constant(5)));
    }

    @Test
    void divisionTest() {        
        Division d1 = new Division(new Constant(3), new Constant(6)); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            d1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator";
        String actualMessage1 = exception1.getMessage();
    
        assertTrue(actualMessage1.contains(expectedMessage1));

        assertFalse(d1.isConstant()); 
        assertFalse(d1.isCommand()); 
        assertTrue(d1.getName().contains("/"));
        assertEquals(100, d1.getPriority());

        assertEquals("3.0 / 6.0", d1.toString()); 

        SymbolicExpression d1Eval = evaluator.evaluate(d1, stack); 
        assertTrue(d1Eval.equals(new Constant(0.5))); 

        assertThrows(RuntimeException.class, () -> {
            Division d2 = new Division(null, null);
            evaluator.evaluate(d2, stack); 
        });

        Division d3 = new Division(new Constant(3), new Constant(5));
        Constant c1 = new Constant(8);
        assertNotEquals(d3, c1);
    }

    @Test
    void expTest() {       
        Exp e1 = new Exp(new Constant(0)); 

        Exception exception = assertThrows(RuntimeException.class, () -> {
            e1.getValue(); 
        });
    
        String expectedMessage = "getValue() called on expression with no operator";
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));        
        
        assertFalse(e1.isConstant()); 
        assertFalse(e1.isCommand()); 
        assertEquals(100, e1.getPriority());
        assertTrue(e1.getName().contains("e^"));

        assertEquals("e^ 0.0", e1.toString());

        SymbolicExpression e1Eval = evaluator.evaluate(e1, stack); 
        assertEquals("1.0", e1Eval.toString()); 
        assertTrue(e1Eval.equals(new Constant(1)));

        Addition e2 = new Addition(new Exp(new Cos(new Multiplication(new Addition(new Constant(3), new Variable("r")), new Variable("u")))), new Constant(4)); 
        assertEquals("e^ (cos ((3.0 + r) * u)) + 4.0", e2.toString()); 

        Assignment a1 = new Assignment(new Negation(new Constant(3)), new Variable("r")); 
        evaluator.evaluate(a1, stack); 
        Assignment a2 = new Assignment(new Constant(1), new Variable("u")); 
        evaluator.evaluate(a2, stack); 
    }

    @Test
    void logTest() {       
        Log l1 = new Log(new Constant(1)); 

        Exception exception = assertThrows(RuntimeException.class, () -> {
            l1.getValue(); 
        });
    
        String expectedMessage = "getValue() called on expression with no operator";
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));        
        
        assertFalse(l1.isConstant()); 
        assertFalse(l1.isCommand()); 
        assertEquals(100, l1.getPriority());
        assertTrue(l1.getName().contains("log"));

        assertEquals("log 1.0", l1.toString()); 

        SymbolicExpression l1Eval = evaluator.evaluate(l1, stack); 
        assertEquals("0.0", l1Eval.toString()); 
        assertTrue(l1Eval.equals(new Constant(0)));

        Addition l2 = new Addition(new Log(new Cos(new Multiplication(new Addition(new Constant(3), new Variable("r")), new Variable("u")))), new Constant(4)); 
        assertEquals("log (cos ((3.0 + r) * u)) + 4.0", l2.toString()); 

        Assignment a1 = new Assignment(new Negation(new Constant(3)), new Variable("r")); 
        evaluator.evaluate(a1, stack); 
        Assignment a2 = new Assignment(new Constant(1), new Variable("u")); 
        evaluator.evaluate(a2, stack); 
        
        SymbolicExpression l2Eval = evaluator.evaluate(l2, stack); 
        assertTrue(l2Eval.equals(new Constant(4)));
    }

    @Test
    void multiplicationTest() {        
        Multiplication m1 = new Multiplication(new Constant(2), new Constant(6)); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            m1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator";
        String actualMessage1 = exception1.getMessage();
    
        assertTrue(actualMessage1.contains(expectedMessage1));

        assertFalse(m1.isConstant()); 
        assertFalse(m1.isCommand()); 
        assertTrue(m1.getName().contains("*"));
        assertEquals(100, m1.getPriority());

        assertEquals("2.0 * 6.0", m1.toString()); 

        SymbolicExpression m1Eval = evaluator.evaluate(m1, stack); 
        assertTrue(m1Eval.equals(new Constant(12))); 

        assertThrows(RuntimeException.class, () -> {
            Multiplication m2 = new Multiplication(null, null);
            evaluator.evaluate(m2, stack);  
        });

        Multiplication m3 = new Multiplication(new Constant(3), new Constant(5));
        Constant c1 = new Constant(8);
        assertNotEquals(m3, c1);
    }

    @Test
    void NamesconstantsTest() {
        assertEquals(Math.PI, Constants.namedConstants.get("pi"));
        assertEquals(Math.E, Constants.namedConstants.get("e"));
        assertEquals(42.0, Constants.namedConstants.get("Answer"));
        assertEquals(6.022140857 * Math.pow(10, 23), Constants.namedConstants.get("L"));
        assertNull(Constants.namedConstants.get("UnknownConstant"));
        
        NamedConstant n1 = new NamedConstant("x", 6); 

        assertEquals(n1.getValue(), 6);
        assertTrue(n1.isNamedConstant()); 
        assertFalse(n1.isCommand()); 
        assertEquals(100, n1.getPriority());

        Exception exception = assertThrows(RuntimeException.class, () -> {
            n1.getName(); 
        });
    
        String expectedMessage = "getName() called on expression with no name"; 
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));

        assertEquals("x", n1.toString()); 

        SymbolicExpression n1Eval = evaluator.evaluate(n1, stack); 
        assertTrue(n1Eval.equals(new Constant(6)));
    }

    @Test
    void negationTest() {        
        Negation n1 = new Negation(new Constant(4)); 
        Negation n2 = new Negation(new Division(new Constant(10), new Constant(5))); 

        Exception exception = assertThrows(RuntimeException.class, () -> {
            n1.getValue(); 
        });
    
        String expectedMessage = "getValue() called on expression with no operator";
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));        
        
        assertFalse(n1.isConstant()); 
        assertFalse(n1.isCommand()); 
        assertEquals(100, n1.getPriority());
        assertTrue(n1.getName().contains("-"));

        assertEquals("- 4.0", n1.toString()); 
        assertEquals("- (10.0 / 5.0)", n2.toString()); 

        SymbolicExpression n1Eval = evaluator.evaluate(n1, stack); 
        SymbolicExpression n2Eval = evaluator.evaluate(n2, stack);  
        assertTrue(n1Eval.equals(new Constant(-4)));
        assertTrue(n2Eval.equals(new Constant(-2)));
    }

    @Test
    void quitTest() {        
        Quit q1 = Quit.instance();  
        Quit q2 = Quit.instance(); 
        assertEquals(q1, q2);
        assertTrue(q1.equals(q2));

        assertEquals(q1.getName(), "quit");
        assertTrue(q1.isCommand());
        assertFalse(q1.isConstant());
        assertEquals(q1.getPriority(), 100);

        assertThrows(RuntimeException.class, () -> {
            q1.getValue(); 
            q1.getVariable(); 
            evaluator.evaluate(q1, stack); 
        });

        Vars v = Vars.instance(); 
        assertNotEquals(q1, v);
        assertNotEquals(q2, v);
    }

    @Test
    void sinTest() {        
        Sin s1 = new Sin(new Constant(Math.PI/2)); 

        Exception exception = assertThrows(RuntimeException.class, () -> {
            s1.getValue(); 
        });
    
        String expectedMessage = "getValue() called on expression with no operator";
        String actualMessage = exception.getMessage();
        assertTrue(actualMessage.contains(expectedMessage));        
        
        assertFalse(s1.isConstant()); 
        assertFalse(s1.isCommand()); 
        assertEquals(100, s1.getPriority());
        assertTrue(s1.getName().contains("sin"));

        assertEquals("sin 90.0", new Sin(new Constant(90)).toString()); 

        SymbolicExpression s1Eval = evaluator.evaluate(s1, stack); 
        assertTrue(s1Eval.equals(new Constant(1)));

        Addition s2 = new Addition(new Sin(new Multiplication(new Constant(Math.PI/2), new Variable("u"))), new Constant(4)); 
        Assignment a1 = new Assignment(new Negation(new Constant(87)), new Variable("r")); 
        evaluator.evaluate(a1, stack); 
        Assignment a2 = new Assignment(new Constant(1), new Variable("u")); 
        evaluator.evaluate(a2, stack); 
        
        SymbolicExpression s2Eval = evaluator.evaluate(s2, stack); 
        assertTrue(s2Eval.equals(new Constant(5)));
    }

    @Test
    void subtractionTest() {
        Subtraction s1 = new Subtraction(new Constant(1), new Constant(6)); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            s1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator";
        String actualMessage1 = exception1.getMessage();
    
        assertTrue(actualMessage1.contains(expectedMessage1));

        assertFalse(s1.isConstant()); 
        assertFalse(s1.isCommand()); 
        assertTrue(s1.getName().contains("-"));
        assertEquals(50, s1.getPriority());

        assertEquals("1.0 - 6.0", s1.toString()); 

        SymbolicExpression s1Eval = evaluator.evaluate(s1, stack); 
        SymbolicExpression s2Eval = evaluator.evaluate(new Negation(new Constant(5)),stack); 
        assertTrue(s1Eval.equals(s2Eval)); 

        assertThrows(RuntimeException.class, () -> {
            Subtraction s2 = new Subtraction(null, null);
            evaluator.evaluate(s2, stack); 
        });

        Subtraction d3 = new Subtraction(new Constant(3), new Constant(5));
        Constant c1 = new Constant(8);
        assertNotEquals(d3, c1);
    }

    @Test
    void symbolicExpressionTest() {        
        SymbolicExpression s1 = new Constant(1); 
        SymbolicExpression s2 = new Multiplication(new Log(new Constant(1)), new Variable("x")); 
        assertTrue(s1.isConstant());
        assertFalse(s2.isConstant());

        SymbolicExpression s3 = Quit.instance(); 
        assertTrue(s3.isCommand());

        assertThrows(RuntimeException.class, () -> {
            s1.getName(); 
            s2.getName(); 
            s3.getName(); 

            s1.getValue(); 
            s2.getValue(); 
            s3.getValue(); 

            s1.getVariable(); 
            s2.getVariable(); 
            s3.getVariable(); 

            evaluator.evaluate(s3, stack);  
        });

        assertEquals(evaluator.evaluate(s1, stack), new Constant(1)); 
        assertEquals(evaluator.evaluate(s2, stack).toString(), "0.0 * x"); 
    }

    @Test
    void unaryTest() {       
        Unary u1 = new Negation(new Variable("x"));
        assertEquals("- (x)", u1.toString());
   
        Unary u2 = new Negation(new Variable("a"));
        Unary u3 = new Negation(new Variable("a"));
        assertTrue(u2.equals(u3));
   
        Unary u4 = new Negation(new Constant(2));
        Unary u5 = new Sin(new Constant(2));
        assertFalse(u4.equals(u5));

        assertFalse(u1.isCommand());
        assertFalse(u1.isConstant());

        assertThrows(RuntimeException.class, () -> {
            u1.getName(); 
            u1.getValue(); 
            u1.getVariable();  
        });

        assertEquals(evaluator.evaluate(u4, stack), new Constant(-2));
    }

    @Test
    void variableTest() {        
        Variable v1 = new Variable("x"); 

        Exception exception1 = assertThrows(RuntimeException.class, () -> {
            v1.getValue(); 
        });
    
        String expectedMessage1 = "getValue() called on expression with no operator"; 
        String actualMessage1 = exception1.getMessage();
        assertTrue(actualMessage1.contains(expectedMessage1));

        assertEquals(v1.getVariable(), new Variable("x"));
        assertFalse(v1.isConstant()); 
        assertFalse(v1.isCommand()); 
        assertEquals(100, v1.getPriority());

        Exception exception2 = assertThrows(RuntimeException.class, () -> {
            v1.getName(); 
        });
    
        String expectedMessage2 = "getName() called on expression with no name"; 
        String actualMessage2 = exception2.getMessage();
        assertTrue(actualMessage2.contains(expectedMessage2));

        assertEquals("x", v1.toString()); 

        SymbolicExpression v1Eval = evaluator.evaluate(v1, stack); 
        assertTrue(v1Eval.equals(new Variable("x")));
    }

    @Test
    void varsTest() {        
        Vars v1 = Vars.instance();  
        Vars v2 = Vars.instance(); 
        assertEquals(v1, v2);
        assertTrue(v1.equals(v2));
        
        assertEquals(v1.getName(), "vars");
        assertTrue(v1.isCommand());
        assertFalse(v1.isConstant());
        assertEquals(v1.getPriority(), 100);

        assertThrows(RuntimeException.class, () -> {
            v1.getValue(); 
            v1.getVariable(); 
            evaluator.evaluate(v1, stack); 
        });

        Clear c = Clear.instance(); 
        assertNotEquals(v1, c);
        assertNotEquals(v2, c);
    }

    @Test
    void scopeTest() {
        SymbolicExpression s1 = new Addition(new Assignment(new Constant(2), new Variable("x")), new Negation(new Constant(4))); 
        Scope scope = new Scope(s1); 

        assertEquals(scope.getName(), "scope");
        assertEquals(scope.getPriority(), 0);
        assertEquals(scope.getScope(), s1);
        assertEquals(scope.toString(), "{(2.0 = x) + - 4.0}");

        assertEquals(evaluator.evaluate(scope, stack), new Constant(-2));
    }

    @Test
    void scopeStackTest() {
        Variable v1 = new Variable("x");
        SymbolicExpression s1 = new Constant(42); 
        stack.put(v1, s1);
        assertEquals(s1, stack.get(v1));

        stack.pushEnvironment();
        stack.put(v1, s1);
        assertEquals(s1, stack.get(v1));
    
        Variable v2 = new Variable("y");
        SymbolicExpression s2 = new Constant(3);
        stack.pushEnvironment();
        stack.put(v2, s2);
        stack.pushEnvironment();
        assertEquals(s2, stack.get(v2));
    
        assertNull(stack.get(new Variable("o")));
    
        stack = new ScopeStack(stack);
        stack.pushEnvironment();
        assertTrue(stack.getLastEnv().equals(stack));

        stack.popEnvironment();
        assertEquals(0, stack.getLastEnv().size());
    
        Variable v3 = new Variable("w");
        SymbolicExpression s3 = new Constant(42);
        SymbolicExpression s4 = new Constant(100);

        stack.put(v3, s3);
        stack.pushEnvironment();
        stack.put(v3, s4);

        assertEquals(s4, stack.get(v3));
    }

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }

}