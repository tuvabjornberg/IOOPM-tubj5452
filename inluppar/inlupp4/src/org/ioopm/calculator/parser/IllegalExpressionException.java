package org.ioopm.calculator.parser;

/**
 * A subclass of RuntimeException. It is thrown when an 
 * expression provided to the parser is illegal or invalid.
 */
public class IllegalExpressionException extends RuntimeException {

    /**
     * Constructs a new IllegalExpressionException with no message.
     */
    public IllegalExpressionException() {
        super();
    }

    /**
     * Constructs a new IllegalExpressionException with the specified message.
     *
     * @param msg The message.
     */
    public IllegalExpressionException(String msg) {
        super(msg);
    }
}
