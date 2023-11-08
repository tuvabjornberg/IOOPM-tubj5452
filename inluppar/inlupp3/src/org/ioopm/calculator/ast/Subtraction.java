package org.ioopm.calculator.ast;

/**
 *A subclass of Binary, representing the subtraction operation.
 */
public class Subtraction extends Binary {

    /**
     * Constructs a Subtraction object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the subtraction operator.
     *
     * @return The string representation of the subtraction operator ("-").
     */
    @Override
    public String getName() {
        return "-";
    }

    /**
     * Returns the priority of the subtraction operation.
     *
     * @return The priority value of 50 for subtraction.
     */
    @Override
    public int getPriority() {
        return 50;
    }

    /**
     * Evaluates the subtraction expression, either performing the subtraction if both operands are constants,
     * or returning a new Subtraction expression with the evaluated operands.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the subtraction operation.
     */
    @Override
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rhsEvaluated = this.getRhs().eval(vars);

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() - rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Subtraction(lhsEvaluated, rhsEvaluated);
        }
    }
}
