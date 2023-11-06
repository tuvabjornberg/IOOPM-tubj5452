package org.ioopm.calculator.ast;
public abstract class SymbolicExpression
{

    public SymbolicExpression() {

    }

    public boolean isConstant() {
        return false; 
    }

    public String getName() throws RuntimeException {
        throw new RuntimeException("getName() called on expression with no operator"); 
    }

    public int getPriority() {
        return 100; 
    }

    public double getValue() throws RuntimeException {
        throw new RuntimeException("getValue() called on expression with no operator"); 
    }

    public Variable getVariable() throws RuntimeException {
        throw new RuntimeException("gatVariable() called on expression with no variable"); 
    }

    public abstract SymbolicExpression eval(Environment vars);

    public boolean isCommand() {
        return false; 
    }
}