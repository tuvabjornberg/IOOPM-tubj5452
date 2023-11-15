package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Binary, representing the addition operation. 
 */
public class Addition extends Binary {
    /**
     * Constructs an Addition object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Addition(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the addition operator.
     *
     * @return The string representation of the addition operator ("+").
     */
    @Override
    public String getName() {
        return "+";
    }

    /**
     * Returns the priority of the addition operation.
     *
     * @return The priority value of 50 for addition.
     */
    @Override
    public int getPriority() {
        return 50;
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
