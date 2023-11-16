package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Command, representing an environment of variables
 */
public class Vars extends Command {
    private static final Vars theInstance = new Vars();

    /**
     * Default constructor for the Vars class.
     */
    private Vars() {}

    /**
     * Get the single instance of the vars command.
     *
     * @return The instance of the Vars command.
     */
    public static Vars instance() {
        return theInstance;
    }

    /**
     * Returns the name of the vars operator.
     *
     * @return The string representation of vars.
     */
    public String getName() {
        return "vars"; 
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