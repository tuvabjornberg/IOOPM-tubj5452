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
    @Override
    public boolean isCommand() {
        return true;
    }
}
