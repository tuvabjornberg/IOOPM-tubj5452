package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Unary, representing the exponential (e^x) operation.
 */
public class Exp extends Unary {

    /**
     * Constructs an Exp object with the given operand.
     *
     * @param argument The operand of the exponential operation.
     */
    public Exp(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the exponential operator.
     *
     * @return The string representation of the exponential operator ("e^").
     */
    @Override
    public String getName() {
        return "e^";
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
