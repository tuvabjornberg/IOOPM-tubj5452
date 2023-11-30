package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*;

public class End extends Command{
    private static final End theInstance = new End();

    private End() {}

    public static End instance() {
        return theInstance;
    }

    @Override
    public String getName(){
        return "end";
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