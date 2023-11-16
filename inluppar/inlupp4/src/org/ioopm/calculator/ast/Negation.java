package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Unary, representing the negation operation.
 */
public class Negation extends Unary {

    /**
     * Constructs a Negation object with the given operand.
     *
     * @param argument The operand of the negation operation.
     */
    public Negation(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the negation operator.
     *
     * @return The string representation of the negation operator ("-").
     */
    @Override
    public String getName() {
        return "-";
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
