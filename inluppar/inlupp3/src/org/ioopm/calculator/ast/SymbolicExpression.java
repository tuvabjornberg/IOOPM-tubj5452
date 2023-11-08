package org.ioopm.calculator.ast; 
/**
 * An abstract superclass representing a common interface for symbolic expressions. 
 */
public abstract class SymbolicExpression {

    /**
     * Default constructor for the SymbolicExpression class.
     */
    public SymbolicExpression() {}

    /**
     * Checks if the symbolic expression is a constant.
     *
     * @return true if the expression is a constant, false otherwise.
     */
    public boolean isConstant() {
        return false;
    }
    
    /**
     * Checks if the symbolic expression is a command.
     *
     * @return true if the expression is a command, false otherwise.
     */
    public boolean isCommand() {
        return false;
    }

    /**
     * Returns the name of the symbolic expression.
     *
     * @return The name of the expression.
     * @throws RuntimeException If called on an expression with no operator.
     */
    public String getName() throws RuntimeException {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    /**
     * Returns the priority of the symbolic expression.
     *
     * @return The priority of the expression.
     */
    public int getPriority() {
        return 100;
    }

    /**
     * Returns the numerical value of the symbolic expression.
     *
     * @return The numerical value of the expression.
     * @throws RuntimeException If called on an expression with no operator.
     */
    public double getValue() throws RuntimeException {
        throw new RuntimeException("getValue() called on expression with no operator");
    }

    /**
     * Returns the variable contained in the symbolic expression.
     *
     * @return The variable in the expression.
     * @throws RuntimeException If called on an expression with no variable.
     */
    public Variable getVariable() throws RuntimeException {
        throw new RuntimeException("getVariable() called on expression with no variable");
    }

    /**
     * Evaluates the symbolic expression using the provided environment of variables.
     *
     * @param vars The environment containing variable values.
     * @return The result of evaluating the expression.
     */
    public abstract SymbolicExpression eval(Environment vars);
}