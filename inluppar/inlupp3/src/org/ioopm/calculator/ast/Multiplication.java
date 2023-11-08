package org.ioopm.calculator.ast;

/**
 * A subclass of Binary, representing the multiplication operation. 
 */
public class Multiplication extends Binary {

    /**
     * Constructs a Multiplication object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the multiplication operator.
     *
     * @return The string representation of the multiplication operator ("*").
     */
    @Override
    public String getName() {
        return "*";
    }

    /**
     * Evaluates the multiplication expression, either performing the multiplication if both operands are constants,
     * or returning a new Multiplication expression with the evaluated operands.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the multiplication operation.
     */
    @Override
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rhsEvaluated = this.getRhs().eval(vars);

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() * rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Multiplication(lhsEvaluated, rhsEvaluated);
        }
    }
}
