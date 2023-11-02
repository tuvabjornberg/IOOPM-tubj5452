package org.ioopm.calculator.ast;


public abstract class SymbolicExpression
{

    public SymbolicExpression() {

    }

    public boolean isConstant() {
        return false; 
    }

    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator"); 
    }

    public int getPriority() {
        return 100; 
    }

    public double getValue() {
        throw new RuntimeException("getValue() called on expression with no operator"); 
    }
}