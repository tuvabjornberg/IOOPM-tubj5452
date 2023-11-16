package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 
/**
 * A subclass of Unary, representing the cos operation.
 */
public class Cos extends Unary {

    /**
     * Constructs a Cos object with the given operand.
     *
     * @param argument The operand of the cosine operation.
     */
    public Cos(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the cosine operator.
     *
     * @return The string representation of the cosine operator ("cos").
     */
    @Override
    public String getName() {
        return "cos";
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
