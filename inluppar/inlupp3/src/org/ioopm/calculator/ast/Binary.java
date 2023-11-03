package org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs; 
        this.rhs = rhs; 
    }

    public String toString() {
        int lhsPriority = this.lhs.getPriority(); 
        int rhsPriority = this.rhs.getPriority(); 
        int currentPriority = this.getPriority(); 

        if (lhsPriority < currentPriority && rhsPriority < currentPriority) {
            return "("+ this.lhs.toString() + ") " + this.getName() + " (" + this.rhs.toString() + ")"; 
        } else if (lhsPriority < currentPriority) {
            return "("+ this.lhs.toString() + ") " + this.getName() + " " + this.rhs.toString(); 
        } else if (rhsPriority < currentPriority) {
            return this.lhs.toString() + " " + this.getName() + " (" + this.rhs.toString() + ")"; 
        } else {
            return this.lhs.toString() + " " + this.getName() + " " + this.rhs.toString(); 
        }
    }
}