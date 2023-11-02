package org.ioopm.calculator.ast;

public class Negation extends Unary {

    public Negation(SymbolicExpression operand) {
        super(operand); 
    }

    public String getName() {
        return "-"; 
    }
}