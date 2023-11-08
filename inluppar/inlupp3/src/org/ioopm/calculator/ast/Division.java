package org.ioopm.calculator.ast;

/**
 * A subclass of Binary, representing the division operation. 
 */
public class Division extends Binary {

    /**
     * Constructs a Division object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Division(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the division operator.
     *
     * @return The string representation of the division operator ("/").
     */
    public String getName() {
        return "/";
    }

    /**
     * Evaluates the division expression, either performing the division if both operands are constants,
     * or returning a new Division expression with the evaluated operands.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the division operation.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rhsEvaluated = this.getRhs().eval(vars);

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant() && rhsEvaluated.getValue() != 0) {
            double result = lhsEvaluated.getValue() / rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Division(lhsEvaluated, rhsEvaluated);
        }
    }
}
