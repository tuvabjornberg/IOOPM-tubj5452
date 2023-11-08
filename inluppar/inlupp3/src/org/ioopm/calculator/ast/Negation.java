package org.ioopm.calculator.ast;

/**
 * A subclass of Unary, representing the negation operation.
 */
public class Negation extends Unary {

    /**
     * Constructs a Negation object with the given operand.
     *
     * @param argument The operand of the negation operation.
     */
    public Negation(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the negation operator.
     *
     * @return The string representation of the negation operator ("-").
     */
    public String getName() {
        return "-";
    }

    /**
     * Evaluates the negation expression.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the negation operation.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = getArg().eval(vars);

        if (arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else {
            return new Negation(arg);
        }
    }
}
