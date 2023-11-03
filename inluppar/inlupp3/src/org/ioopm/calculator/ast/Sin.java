package org.ioopm.calculator.ast;

public class Sin extends Unary {

    public Sin(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "sin"; 
    }
}