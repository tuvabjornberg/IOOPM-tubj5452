package org.ioopm.calculator.ast;

public class Unary extends SymbolicExpression {
    private SymbolicExpression operand; 

    public Unary(SymbolicExpression operand) {
        this.operand = operand; 
    }
    
}