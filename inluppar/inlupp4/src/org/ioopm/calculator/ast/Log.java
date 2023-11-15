package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 
/**
 * A subclass of Unary, representing logarithm (log) operation.
 */
public class Log extends Unary {

    /**
     * Constructs a Log object with the given operand.
     *
     * @param argument The operand of the logarithm operation.
     */
    public Log(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the logarithm operator.
     *
     * @return The string representation of the logarithm operator ("log").
     */
    @Override
    public String getName() {
        return "log";
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
