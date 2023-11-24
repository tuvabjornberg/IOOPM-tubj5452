package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Command, representing to clear. 
 */
public class Clear extends Command{
    private static final Clear theInstance = new Clear();

    /**
     * Default constructor for the Clear class.
     */
    private Clear() {}

    /**
     * Get the single instance of the Clear command.
     *
     * @return The instance of the Clear command.
     */
    public static Clear instance() {
        return theInstance;
    }

    /**
     * Returns the name of the clear operator.
     *
     * @return The string representation of clear.
     */
    @Override
    public String getName() {
        return "clear"; 
    }

    /**
     * Accepts a visitor for the Visitor pattern.
     * 
     * @param v The visitor instance.
     * @return Result of the visitor's processing.
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
