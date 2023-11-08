package org.ioopm.calculator.ast; 
/**
 * An abstarct subclass of SymbolicExpression, representing binary operations
 * involving two operands. 
 */
public abstract class Binary extends SymbolicExpression {
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    /**
     * Constructs a Binary object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs;
        this.rhs = rhs;
    }

    /**
     * Retrieves the left-hand side operand of the binary expression.
     *
     * @return The left-hand side operand.
     */
    public SymbolicExpression getLhs() {
        return lhs;
    }   

    /**
     * Retrieves the right-hand side operand of the binary expression.
     *
     * @return The right-hand side operand.
     */
    public SymbolicExpression getRhs() {
        return rhs;
    }

    /**
     * Generates a string representation of the binary expression. The string may include
     * parentheses based on the priority of the operands. 
     *
     * @return A string representation of the binary expression.
     */
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

    /**
     * Checks if object is instance of Binary type, to later check
     * eqaulity to. 
     *
     * @param other The object to compare for equality.
     * @return true if the objects are equal, false otherwise.
     */
    public boolean equals(Object other) {
        if (other instanceof Binary) {
            return this.equals((Binary) other); 
        } else {
            return false; 
        }
    }

    /**
     * Checks if the current Binary object is equal to another Binary object. 
     *
     * @param other The Binary object to compare for equality.
     * @return true if the Binary objects are equal, false otherwise.
     */
    public boolean equals(Binary other) {
        String operator1 = this.getName(); 
        String operator2 = other.getName(); 
        boolean sameOperator = operator1.equals(operator2); 

        String lhs1 = this.lhs.toString(); 
        String lhs2 = other.lhs.toString(); 

        String rhs1 = this.rhs.toString(); 
        String rhs2 = other.rhs.toString(); 
        
        boolean sameToSame = lhs1.equals(lhs2) && rhs1.equals(rhs2);
        boolean sameToOposite = lhs1.equals(rhs2) && rhs1.equals(lhs2); 

        return (sameToSame || sameToOposite) && sameOperator;
    }
}
