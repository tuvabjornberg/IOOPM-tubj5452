package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 
/**
 * A subclass of Unary, representing the sin operation.
 */
public class Sin extends Unary {

    /**
     * Constructs a Sin object with the given operand.
     *
     * @param argument The operand of the sine operation.
     */
    public Sin(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the sine operator.
     *
     * @return The string representation of the sine operator ("sin").
     */
    @Override
    public String getName() {
        return "sin";
    }

    /**
     * Accepts a visitor for the Visitor pattern.
     * @param v The visitor instance.
     * @return Result of the visitor's processing.
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
