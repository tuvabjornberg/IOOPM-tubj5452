package org.ioopm.calculator;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.ast. *; 
import org.ioopm.calculator.parser. *; 

public class IntegrationTests {

    private CalculatorParser parser;
    private Environment vars;  

    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
        vars = new Environment(); 
        parser = new CalculatorParser();
    }

    void afterParseTest(SymbolicExpression arg, String strToParse) {
        SymbolicExpression e1 = null; 
        try {
            e1 = parser.parse(strToParse, vars); 
            assertTrue(e1.equals(arg)); 
        } catch (IOException e) {
            fail("Unexpected exception was thrown");
        }
    }

    @Test
    void constantParserTest() {
        Constant c1 = new Constant(6); 
        String strC1 = c1.toString(); 
        String strInvalid = "6"; 

        assertEquals("6.0", strC1);
        assertNotEquals(strInvalid, strC1); 

        afterParseTest(c1, strC1);
        afterParseTest(c1, strInvalid);
    }

    @Test
    void namedConstantParserTest() {
        assertEquals(42.0, Constants.namedConstants.get("Answer"));
        afterParseTest(new Constant(Constants.namedConstants.get("Answer")), "42");
    }

    @Test
    void variableParserTest() {
        Variable v1 = new Variable("x"); 
        String strV1 = v1.toString(); 

        assertEquals("x", strV1);
        assertNotEquals("x", v1);

        afterParseTest(v1, strV1);

        Variable v2 = new Variable("dlefjwowknoirjewiu948r9w"); 
        String strV2 = v2.toString(); 

        assertEquals("dlefjwowknoirjewiu948r9w", strV2);

        afterParseTest(v2, strV2);

        assertThrows(RuntimeException.class, () -> {
            parser.parse("teststr|ngwith,symb@ls", vars); 
        });
    }

    @Test
    void unaryParserTest() {
        Cos cos1 = new Cos(new Constant(0)); 
        String strC1 = cos1.toString(); 

        assertEquals("cos 0.0", strC1);
        afterParseTest(cos1, strC1);

        Negation n1 = new Negation(cos1); 
        String strN1 = n1.toString(); 
        assertEquals("- (cos 0.0)", strN1);
        afterParseTest(n1, strN1);

        Constant c1 = new Constant(4); 
        Negation n2 = new Negation(c1); 
        String strN2 = n2.toString(); 
        assertEquals("- 4.0", strN2);
        afterParseTest(n2, strN2);

        Negation n3 = new Negation(new Negation(new Negation(c1))); 
        String strN3 = n3.toString(); 
        assertEquals("- (- (- 4.0))", strN3);
        afterParseTest(n3, strN3);
    }

    @Test 
    void binaryParserTest() {
        SymbolicExpression s1 = new Addition(new Constant(42), new Negation(new Constant(4711))); 
        String strS1 = s1.toString(); 
        assertEquals("42.0 + - 4711.0", strS1);
        afterParseTest(s1, strS1);

        SymbolicExpression s2 = new Multiplication(new Addition(new Constant(4), new Variable("y")), new Subtraction(new Constant(9), new Constant(7))); 
        String strS2 = s2.toString(); 
        assertEquals("(4.0 + y) * (9.0 - 7.0)", strS2);
        afterParseTest(s2, strS2);
    }

    @Test
    void parenthesesParserTest() {
        Assignment a1 = new Assignment(new Constant(1), new Variable("x")); 
        String strA1 = a1.toString(); 
        String strS1 = "(1.0 = x)"; 

        assertNotEquals(strA1, strS1);
        assertEquals("1.0 = x", strA1);

        afterParseTest(a1, strA1);
        afterParseTest(a1, strS1);

        assertThrows(RuntimeException.class, () -> {
            parser.parse("(x", vars); 
        });
    }

    @Test
    void whiteSpaceParserTest() {
        Addition a1 = new Addition(new Variable("x"), new Constant(3)); 
        String strA1 = a1.toString(); 
        String extraWiteSpace = "x     + 3.0   "; 

        assertNotEquals(strA1, extraWiteSpace);
        assertEquals("x + 3.0", strA1);
        assertNotEquals("x + 3.0", extraWiteSpace);

        afterParseTest(a1, strA1);
        afterParseTest(a1, extraWiteSpace);
    }

    @Test
    void complexExpTest() {
        SymbolicExpression s2 = new Division(new Multiplication(new Division(new Addition(new Constant(5), new Variable("x")), new Constant(2)), new Constant(1)), new Subtraction(new Constant(9), new Sin(new Constant(9)))); 
        String strS2 = s2.toString(); 

        assertEquals("(5.0 + x) / 2.0 * 1.0 / (9.0 - sin 9.0)", strS2);
        afterParseTest(s2, strS2);
    }

    @AfterEach
    void tearDown() {

    }

    @AfterAll
    static void tearDownAll() {
    }
}