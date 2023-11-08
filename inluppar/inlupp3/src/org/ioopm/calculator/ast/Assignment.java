package org.ioopm.calculator.ast;

import org.ioopm.calculator.parser.IllegalExpressionException;

/**
 * A subclass of Binary, representing the assignment operation. 
 */
public class Assignment extends Binary {

    /**
     * Constructs an Assignment object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the assignment operator.
     *
     * @return The string representation of the assignment operator ("=").
     */
    public String getName() {
        return "=";
    }

    /**
     * Returns the priority of the assignment operation.
     *
     * @return The priority value of 0 for assignment.
     */
    public int getPriority() {
        return 0;
    }

    /**
     * Evaluates the assignment expression, updating the environment with the assigned variable
     * and returning the value of the assigned variable or constant.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the assignment operation.
     * @throws IllegalExpressionException If trying to redefine a named constant.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rhs = this.getRhs();

        if (!rhs.isConstant()) {
            vars.put(new Variable(rhs.toString()), lhsEvaluated);

            if (lhsEvaluated.isConstant()) {
                return new Constant(lhsEvaluated.getValue());
            } else {
                return lhsEvaluated;
            }
        } else {
            throw new IllegalExpressionException("Error: cannot redefine named constant");
        }
    }
}
