package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList; 

/**
 * A subclass of SymbolicExpression, representing a function declaration. 
 */
public class FunctionDeclaration extends SymbolicExpression {
    private Variable functionName; 
    private ArrayList<Variable> parameters; 
    private Sequence body; 

    /**
     * Creates a new FunctionDeclaration instance with the specified function name, parameters, and body.
     *
     * @param functionName The variable representing the function name.
     * @param parameters An ArrayList of Variable objects representing the function parameters.
     * @param body The sequence representing the function body.
     */
    public FunctionDeclaration(Variable functionName, ArrayList<Variable> parameters, Sequence body){
        this.functionName = functionName;
        this.parameters = parameters;
        this.body = body;    
    }

    /**
     * Gets the variable representing the function name.
     *
     * @return The Variable object representing the function name.
     */
    @Override
    public Variable getFuncName() {
        return this.functionName;
    }
    
    /**
     * Gets the sequence representing the function body.
     *
     * @return The Sequence object representing the function body.
     */
    @Override
    public Sequence getSequence() {
        return this.body; 
    }
    
    /**
     * Gets the list of parameters for the function.
     *
     * @return An ArrayList of Variable objects representing the function parameters.
     */
    @Override
    public ArrayList<Variable> getParameters() {
        return this.parameters; 
    }

    /**
     * Gets the FunctionDeclaration object.
     *
     * @return The FunctionDeclaration object.
     */
    @Override
    public FunctionDeclaration getFunctionDeclaration() {
        return this; 
    }

    /**
     * Generates a string representation of a FunctionDeclaration.
     *
     * @return A string representation of the function declaration.
     */
    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("function ").append(functionName.toString()).append("(");

        for (int i = 0; i < parameters.size(); i++) {
            result.append(parameters.get(i));
            if (i < parameters.size() - 1) {
                result.append(", ");
            }
        }

        result.append(")\n");
        result.append(body.toString());
        result.append("end");

        return result.toString();
    }
    

    /**
     * Checks if object is an instance of FunctionDeclaration type, to later check 
     * equality to
     *
     * @param other The object to compare for equality.
     * @return true if the objects are equal, false otherwise.
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof FunctionDeclaration) {
            return this.equals((FunctionDeclaration) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current FunctionDeclaration object is equal to another FunctionDeclaration object.
     *
     * @param other The FunctionDeclaration object to compare for equality.
     * @return true if the FunctionDeclaration objects are equal, false otherwise.
     */
    public boolean equals(FunctionDeclaration other) {
        Variable funcName1 = this.getFuncName();
        Variable funcName2 = other.getFuncName();
        boolean sameFuncName = funcName1.equals(funcName2);

        ArrayList<Variable> params1 = this.getParameters();
        ArrayList<Variable> params2 = other.getParameters();
        boolean sameParams = params1.equals(params2);

        Sequence body1 = this.getSequence();
        Sequence body2 = other.getSequence();
        boolean sameBody = body1.equals(body2);

        return sameFuncName && sameParams && sameBody;
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
