package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList;

public class Sequence extends SymbolicExpression {
    private ArrayList<SymbolicExpression> body;

    public Sequence() {
        this.body = new ArrayList<SymbolicExpression>();
    }

    public void addExpression(SymbolicExpression s){
        this.body.add(s);
    }
    
    public ArrayList<SymbolicExpression> getBody(){
        return this.body;
    }

    public int getSequenceSize() {
        return this.body.size(); 
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
