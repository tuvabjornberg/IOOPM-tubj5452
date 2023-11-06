package org.ioopm.calculator.ast;

public class NamedConstant extends Atom{
    private String name; 
    private double value; 

    public NamedConstant(String name,double value) {
        this.name = name; 
        this.value = value; 
    }

    public boolean isConstant() {
        return true;
    }

    public String toString() {
        return this.name; 
    }

    public double getValue() {
        return this.value; 
    }

    public SymbolicExpression eval(Environment vars) {
        return new Constant(this.value); 
    }

}