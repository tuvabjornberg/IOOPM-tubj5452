package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList; 

public class FunctionDeclaration extends SymbolicExpression {
    private Variable functionName; 
    private ArrayList<Variable> parameters; 
    private Sequence body; 

    public FunctionDeclaration(Variable functionName, ArrayList<Variable> parameters, Sequence body){
        this.functionName = functionName;
        this.parameters = parameters;
        this.body = body;    
    }

    @Override
    public Variable getFuncName() {
        return this.functionName;
    }
    
    @Override
    public Sequence getSequence() {
        return this.body; 
    }
    
    @Override
    public ArrayList<Variable> getParameters() {
        return this.parameters; 
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
