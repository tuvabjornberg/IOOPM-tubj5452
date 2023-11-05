package org.ioopm.calculator.ast;

public class Variable extends Atom {
    private String identifier; 

    public Variable(String identifier) {
        this.identifier = identifier; 
    }

    public Variable getVariable() {
        return this; 
    }

    public String toString() {
        return String.valueOf(this.identifier); 
    }
    
    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }
    
    public boolean equals(Variable other) {
        return this.identifier.equals(other.identifier);
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression retrieved = vars.get(this.getVariable()); 

        if (retrieved != null) {
            return retrieved; 
        } else {
            return new Variable(this.identifier); 
        }
    }

    public int hashCode() {
        return this.identifier.hashCode(); 
    }
}