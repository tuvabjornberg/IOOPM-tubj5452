package org.ioopm.calculator.ast;

/**
 * An an abstract subclass of SymbolicExpression, representing unary operations
 * involving a single operand.
 */
public abstract class Unary extends SymbolicExpression {
    private SymbolicExpression argument = null;

    /**
     * Constructs a Unary object with the given operand.
     *
     * @param argument The operand of the unary expression.
     */
    public Unary(SymbolicExpression argument) {
        this.argument = argument;
    }

    /**
     * Retrieves the operand of the unary expression.
     *
     * @return The operand of the unary expression.
     */
    public SymbolicExpression getArg() {
        return this.argument;
    }

    /**
     * Generates a string representation of the unary expression. The string may include
     * parentheses based on the priority of the operands. 
     *
     * @return A string representation of the unary expression.
     */
    @Override
    public String toString() {
        int argPriority = this.argument.getPriority();
        int currentPriority = this.getPriority();

        if (argPriority < currentPriority || !this.argument.isConstant()) {
            return this.getName() + " (" + this.argument.toString() + ")";
        } else {
            return this.getName() + " " + this.argument.toString();
        }
    }

    /**
     * Checks if object is instance of Binary type, to later check
     * eqaulity to. 
     *
     * @param other The object to compare for equality.
     * @return true if the objects are equal, false otherwise.
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current Unary object is equal to another Unary object. 
     *
     * @param other The Unary object to compare for equality.
     * @return true if the Unary objects are equal, false otherwise.
     */
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
