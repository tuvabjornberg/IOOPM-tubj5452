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

    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other); 
        } else {
            return false; 
        }
    }

    public boolean equals(Unary other) {
        String operator1 = this.getName(); 
        String operator2 = other.getName(); 
        boolean sameOperator = operator1.equals(operator2); 

        String argument1 = this.argument.toString(); 
        String argument2 = other.argument.toString(); 
        boolean sameArgument = argument1.equals(argument2); 

        return sameOperator && sameArgument; 
    }
    
}