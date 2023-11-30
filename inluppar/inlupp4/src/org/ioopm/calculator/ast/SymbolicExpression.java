package org.ioopm.calculator.ast; 

import org.ioopm.calculator.visitor.*;

import java.util.ArrayList;
/**
 * An abstract superclass representing a common interface for symbolic expressions. 
 */
public abstract class SymbolicExpression {

    /**
     * Default constructor for the SymbolicExpression class.
     */
    public SymbolicExpression() {}

    /**
     * Checks if the symbolic expression is a constant.
     *
     * @return Always returns false. 
     */
    public boolean isConstant() {
        return false;
    }

    /**
     * Checks if the symbolic expression is a named constant.
     *
     * @return Always returns false. 
     */
    public boolean isNamedConstant() {
        return false; 
    }
    
    /**
     * Checks if the symbolic expression is a command.
     *
     * @return Always returns false. 
     */
    public boolean isCommand() {
        return false;
    }

    /**
     * Returns the name of the symbolic expression.
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression with no operator.
     */
    public String getName() throws RuntimeException {
        throw new RuntimeException("getName() called on expression with no name");
    }

    /**
     * Returns the priority of the symbolic expression.
     *
     * @return The priority of the expression.
     */
    public int getPriority() {
        return 100;
    }

    /**
     * Returns the numerical value of the symbolic expression.
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression with no operator.
     */
    public double getValue() throws RuntimeException {
        throw new RuntimeException("getValue() called on expression with no operator");
    }

    /**
     * Returns the variable contained in the symbolic expression.
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression with no variable.
     */
    public Variable getVariable() throws RuntimeException {
        throw new RuntimeException("getVariable() called on expression with no variable");
    }

    /**
     * Returns the symbolic expression within a scope. 
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression not in a scope. 
     */
    public SymbolicExpression getScope() {
        throw new RuntimeException("getScope() called on expression non scoped expression"); 
    }

    /**
     * Returns the sequence within a function declaration
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression not having a sequence
     */
    public SymbolicExpression getSequence() {
        throw new RuntimeException("getSequence() called on expression that is not a function"); 
    }

    /**
     * Returns the parameters within a function call
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression not being a function call
     */
    public ArrayList<Variable> getParameters() {
        throw new RuntimeException("getParameters() called on expression that is not a function"); 
    }

    /**
     * Returns a function name 
     *
     * @return A RuntimeException is always thrown. 
     * @throws RuntimeException If called on an expression not being a function 
     */
    public Variable getFuncName() {
        throw new RuntimeException("getParameters() called on expression that is not a function"); 
    }

    /**
     * Accepts a visitor for the Visitor pattern.
     * 
     * @param v The visitor instance.
     * @return A RuntimeException is always thrown.
     * @throws RuntimeException If called on expression which does not allow accept. 
     */
    public SymbolicExpression accept(Visitor v) {
        throw new RuntimeException("accept() called on invalid expression"); 
    }
}