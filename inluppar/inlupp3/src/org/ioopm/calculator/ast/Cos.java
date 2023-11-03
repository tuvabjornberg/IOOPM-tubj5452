package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "cos"; 
    }
}