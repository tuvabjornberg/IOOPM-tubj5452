package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList;

/**
 * A subclass of SymbolicExpression, representing a sequence.
 */
public class Sequence extends SymbolicExpression {
    private ArrayList<SymbolicExpression> body;

    /**
     * Creates a new Sequence instance with an empty body.
     */
    public Sequence() {
        this.body = new ArrayList<SymbolicExpression>();
    }

    /**
     * Adds a symbolic expression to the sequence.
     *
     * @param s The SymbolicExpression to add to the sequence.
     */
    public void addExpression(SymbolicExpression s){
        this.body.add(s);
    }
    
    /**
     * Gets the body of the sequence.
     *
     * @return An ArrayList of SymbolicExpression objects representing the sequence body.
     */
    public ArrayList<SymbolicExpression> getBody(){
        return this.body;
    }

    /**
     * Gets the size of the sequence.
     *
     * @return The number of expressions in the sequence.
     */
    public int getSequenceSize() {
        return this.body.size(); 
    }

    /**
     * Gets the symbolic expression at the specified index in the sequence.
     *
     * @param index The index of the expression in the sequence.
     * @return The SymbolicExpression at the specified index.
     */
    public SymbolicExpression getExpression(int index) {
        return this.body.get(index); 
    }

    /**
     * Generates a string representation of a Sequence.
     *
     * @return A string representation of the sequence.
     */
    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();

        for (SymbolicExpression expression : body) {
            result.append(expression.toString()).append("\n");
        }

        return result.toString(); 
    }

    /**
     * Checks if object is an instance of Sequence type, to later check 
     * equality to
     *
     * @param other The object to compare for equality.
     * @return true if the objects are equal, false otherwise.
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof Sequence) {
            return this.equals((Sequence) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current Sequence object is equal to another Sequence object.
     *
     * @param other The Sequence object to compare for equality.
     * @return true if the Sequence objects are equal, false otherwise.
     */
    public boolean equals(Sequence other) {
        ArrayList<SymbolicExpression> body1 = this.getBody();
        ArrayList<SymbolicExpression> body2 = other.getBody();

        return body1.equals(body2);
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
