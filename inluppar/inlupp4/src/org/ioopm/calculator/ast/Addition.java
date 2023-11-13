package org.ioopm.calculator.ast;

/**
 * A subclass of Binary, representing the addition operation. 
 */
public class Addition extends Binary {
    /**
     * Constructs an Addition object with the given left-hand side and right-hand side operands.
     *
     * @param lhs The left-hand side operand.
     * @param rhs The right-hand side operand.
     */
    public Addition(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Returns the name of the addition operator.
     *
     * @return The string representation of the addition operator ("+").
     */
    @Override
    public String getName() {
        return "+";
    }

    //SymbolicExpression s = new Addition(new Constant(1), new Constant(2)); 

    /**
     * Returns the priority of the addition operation.
     *
     * @return The priority value of 50 for addition.
     */
    @Override
    public int getPriority() {
        return 50;
    }

    /**
     * Evaluates the addition expression, either performing the addition if both operands are constants,
     * or returning a new Addition expression with the evaluated operands.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the addition operation.
     */
    @Override
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rhsEvaluated = this.getRhs().eval(vars);

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() + rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Addition(lhsEvaluated, rhsEvaluated);
        }
    }
}
