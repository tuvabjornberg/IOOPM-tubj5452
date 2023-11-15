package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 
/**
 * A subclass of Atom, representing a variable in a symbolic expression.
 */
public class Variable extends Atom {
    private String identifier;

    /**
     * Constructs a Variable object with the given identifier.
     *
     * @param identifier The name of the variable.
     */
    public Variable(String identifier) {
        this.identifier = identifier;
    }

    /**
     * Returns the Variable object itself.
     *
     * @return The Variable object.
     */
    @Override
    public Variable getVariable() {
        return this;
    }

    /**
     * Returns the string representation of the variable.
     *
     * @return The string representation of the variable.
     */
    public String toString() {
        return String.valueOf(this.identifier);
    }

    /**
     * Checks if the specified object is instance of variable, to later 
     * check equality to the current object. 
     *
     * @param other The object to compare with.
     * @return True if the objects are equal, false otherwise.
     */
    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current variable is equal to the specified variable.
     *
     * @param other The variable to compare with.
     * @return True if the variables are equal, false otherwise.
     */
    public boolean equals(Variable other) {
        return this.identifier.equals(other.identifier);
    }

    /**
     * Returns the hash code value for the variable.
     *
     * @return The hash code value for the variable.
     */
    public int hashCode() {
        return this.identifier.hashCode();
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
