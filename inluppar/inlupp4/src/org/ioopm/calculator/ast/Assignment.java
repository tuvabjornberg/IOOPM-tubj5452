package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

/**
 * A subclass of Binary, representing the assignment operation. 
 */
public class Assignment extends Binary {

    /**
     * Constructs an Assignment object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the assignment operator.
     *
     * @return The string representation of the assignment operator ("=").
     */
    @Override
    public String getName() {
        return "=";
    }

    /**
     * Returns the priority of the assignment operation.
     *
     * @return The priority value of 0 for assignment.
     */
    @Override
    public int getPriority() {
        return 0;
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
