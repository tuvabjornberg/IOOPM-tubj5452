package org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression argument) {
        super(argument); 
    }
    
    public String getName() {
        return "e^"; 
    }
}