package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Command, representing to quit. 
 */
public class Quit extends Command {
    private static final Quit theInstance = new Quit();

    /**
     * Default constructor for the Quit class.
     */
    private Quit() {}

    /**
     * Get the single instance of the Quit command.
     *
     * @return The instance of the Quit command.
     */
    public static Quit instance() {
        return theInstance;
    }

    /**
     * Returns the name of the quit operator.
     *
     * @return The string representation of quit.
     */
    public String getName() {
        return "quit"; 
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