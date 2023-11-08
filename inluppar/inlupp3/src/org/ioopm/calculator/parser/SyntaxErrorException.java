package org.ioopm.calculator.parser;

/**
 * A subclass of RuntimeException. It is thrown when a syntax error 
 * during the parsing occurs. 
 */
public class SyntaxErrorException extends RuntimeException {

    /**
     * Constructs a new SyntaxErrorException with no message.
     */
    public SyntaxErrorException() {
        super();
    }

    /**
     * Constructs a new SyntaxErrorException with the specified message.
     *
     * @param msg The message.
     */
    public SyntaxErrorException(String msg) {
        super(msg);
    }
}
