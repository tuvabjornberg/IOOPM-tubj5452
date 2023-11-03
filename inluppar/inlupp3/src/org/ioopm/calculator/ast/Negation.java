package org.ioopm.calculator.ast;

public class Negation extends Unary {

    public Negation(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "-"; 
    }
}