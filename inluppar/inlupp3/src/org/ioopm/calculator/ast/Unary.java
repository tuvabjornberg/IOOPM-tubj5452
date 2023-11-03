package org.ioopm.calculator.ast;

public class Unary extends SymbolicExpression {
    private SymbolicExpression argument; 

    public Unary(SymbolicExpression argument) {
        this.argument = argument; 
    }

    public String toString() {
        int argPriority = this.argument.getPriority(); 
        int currentPriority = this.getPriority(); 
        if (argPriority < currentPriority) {
            return this.getName() + " (" + this.argument.toString() + ")"; 
        } else {
            return this.getName() + " " + this.argument.toString(); 
        }
    }
    
}