package org.ioopm.calculator.ast;

/**
 * An abstract subclass of SymbolicExpression, representing commands
 * indicating actions.
 */
public abstract class Command extends SymbolicExpression {

    /**
     * Default constructor for the Command class.
     */
    public Command() {}

    /**
     * Checks if the expression is a command.
     *
     * @return true, indicating that the expression is a command.
     */
    public boolean isCommand() {
        return true;
    }

    /**
     * If a command tries to be evaluated an exception will be thrown as commands 
     * may not be evaluated.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression This method throws a RuntimeException indicating that
     *         commands may not be evaluated.
     * @throws RuntimeException Always throws a RuntimeException with the error message
     *         "Error: Commands may not be evaluated".
     */
    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Error: Commands may not be evaluated");
    }
}
