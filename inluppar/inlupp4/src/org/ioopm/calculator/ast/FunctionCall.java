package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression {
    private Variable functionName; 
    private ArrayList<Atom> arguments; 
    
    public FunctionCall(Variable functionName, ArrayList<Atom> arguments) {
        this.functionName = functionName;
        this.arguments = arguments;
    }

    public ArrayList<Atom> getArguments(){
        return this.arguments;
    }
    
    @Override
    public Variable getFuncName() {
        return this.functionName;
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
