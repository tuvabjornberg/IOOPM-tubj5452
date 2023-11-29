package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*;

/**
 * A subclass of SymbolicExpression, representing a a conditional expression with a condition, 
 * an if-case and an else-case. 
 */
public class Conditional extends SymbolicExpression{
    private SymbolicExpression lhs; 
    private SymbolicExpression rhs; 
    private String operand;
    private SymbolicExpression ifBranch;
    private SymbolicExpression elseBranch; 

    /**
     * Constructs a new Conditional object.
     * 
     * @param operand The comparison operand (<, >, <=, >=, ==).
     * @param lhs The left-hand side of the comparison.
     * @param rhs The right-hand side of the comparison.
     * @param ifBranch The expression to evaluate if the condition is true.
     * @param elseBranch The expression to evaluate if the condition is false.
     */
    public Conditional(String operand, SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifBranch, 
                        SymbolicExpression elseBranch) {
        this.lhs = lhs;
        this.rhs = rhs;
        this.operand = operand;
        this.ifBranch = ifBranch;
        this.elseBranch = elseBranch;
    }

    /**
     * Gets the operand of the conditional expression.
     * 
     * @return The operand as a string.
     */
    @Override
    public String getName() {
        return this.operand; 
    }

   /**
     * Gets the left-hand side of the conditional expression.
     * 
     * @return The left-hand side expression.
     */
    public SymbolicExpression getLhs() {
        return this.lhs; 
    }

    /**
     * Gets the right-hand side of the conditional expression.
     * 
     * @return The right-hand side expression.
     */
    public SymbolicExpression getRhs(){
        return this.rhs;
    }

    /**
     * Gets the if-branch of the conditional expression.
     * 
     * @return The expression to evaluate if the condition is true.
     */
    public SymbolicExpression getIfBranch() {
        return this.ifBranch; 
    }

    /**
     * Gets the else-branch of the conditional expression.
     * 
     * @return The expression to evaluate if the condition is false.
     */
    public SymbolicExpression getElseBranch(){
        return this.elseBranch;
    }

    /**
     * Generates a string of the conditional statement
     * 
     * @return String represention of the conditional statement
     */
    @Override
    public String toString() {
        return "if " + lhs.toString() + " " + operand + " " + rhs.toString() + " " + ifBranch.toString() + " else " + elseBranch.toString(); 
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
