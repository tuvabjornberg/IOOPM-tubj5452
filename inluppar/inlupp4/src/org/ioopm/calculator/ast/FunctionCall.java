package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*; 

import java.util.ArrayList;

/**
 * A subclass of SymbolicExpression, representing a function call. 
 */
public class FunctionCall extends SymbolicExpression {
    private Variable functionName; 
    private ArrayList<Atom> arguments; 
    
    /**
     * Constructs a FunctionCall object with the specified function name and arguments.
     *
     * @param functionName The variable representing the function name.
     * @param arguments An ArrayList of Atom objects representing the function arguments.
     */
    public FunctionCall(Variable functionName, ArrayList<Atom> arguments) {
        this.functionName = functionName;
        this.arguments = arguments;
    }

    /**
     * Gets the arguments of the function call.
     *
     * @return An ArrayList of Atom objects representing the function arguments.
     */
    public ArrayList<Atom> getArguments(){
        return this.arguments;
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
     * Generates a string representation of a FunctionCall
     *
     * @return A string representation of the function call.
     */
    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append(functionName.toString()).append("(");

        for (int i = 0; i < arguments.size(); i++) {
            result.append(arguments.get(i).toString());
            if (i < arguments.size() - 1) {
                result.append(", ");
            }
        }

        result.append(")");
        return result.toString();
    }

    /**
     * Checks if object is an instance of FunctionCall type, to later check 
     * equality to
     *
     * @param other The object to compare for equality.
     * @return true if the objects are equal, false otherwise.
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof FunctionCall) {
            return this.equals((FunctionCall) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current FunctionCall object is equal to another FunctionCall object.
     *
     * @param other The FunctionCall object to compare for equality.
     * @return true if the FunctionCall objects are equal, false otherwise.
     */
    public boolean equals(FunctionCall other) {
        Variable funcName1 = this.getFuncName();
        Variable funcName2 = other.getFuncName();
        boolean sameFuncName = funcName1.equals(funcName2);

        ArrayList<Atom> args1 = this.getArguments();
        ArrayList<Atom> args2 = other.getArguments();
        boolean sameArgs = args1.equals(args2);

        return sameFuncName && sameArgs;
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
