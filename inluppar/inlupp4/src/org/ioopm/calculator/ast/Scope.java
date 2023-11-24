package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*;

public class Scope extends SymbolicExpression{
    SymbolicExpression exp;

    /**
     * Constructs a scope expression
     *
     * @param exp The expression within the scope
     */
    public Scope(SymbolicExpression exp){
        this.exp = exp;
    }

    /**
     * Returns the name of the assignment operator.
     *
     * @return The string representation of the assignment operator ("=").
     */
    @Override
    public String getName() {
        return "scope";
    }

    /**
     * Returns the priority of the assignment operation.
     *
     * @return The priority value of 0 for scope.
     */
    @Override
    public int getPriority() {
        return 0;
    }

    /**
     * Returns the expression within the current scope. 
     * 
     * @return The expression in the scope
     */
    @Override
    public SymbolicExpression getScope() {
        return this.exp; 
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

    @Override
    public String toString(){
        return "{" + this.exp + "}";
    }
}