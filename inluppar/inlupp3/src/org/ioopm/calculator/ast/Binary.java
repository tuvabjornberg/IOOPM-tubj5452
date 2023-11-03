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

    public boolean equals(Object other) {
        if (other instanceof Binary) {
            return this.equals((Binary) other); 
        } else {
            return false; 
        }
    }

    public boolean equals(Binary other) {
        //same operator
        //same lhs
        //same rhs
        String operator1 = this.getName(); 
        String operator2 = other.getName(); 
        boolean sameOperator = operator1.equals(operator2); 

        String lhs1 = this.lhs.toString(); 
        String lhs2 = other.lhs.toString(); 

        String rhs1 = this.rhs.toString(); 
        String rhs2 = other.rhs.toString(); 
        
        boolean sameLhs = lhs1.equals(lhs2) || lhs1.equals(rhs2); 
        boolean sameRhs = rhs1.equals(rhs2) || rhs1.equals(lhs2); 

        // 1 + x
        // x + 1 

        return sameOperator && sameLhs && sameRhs; //&& same lhs && same rhs x + 1 = 1 + x  
    }
}