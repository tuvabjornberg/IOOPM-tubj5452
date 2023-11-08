package org.ioopm.calculator.ast;

/**
 * A subclass of Unary, representing the sin operation.
 */
public class Sin extends Unary {

    /**
     * Constructs a Sin object with the given operand.
     *
     * @param argument The operand of the sine operation.
     */
    public Sin(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the sine operator.
     *
     * @return The string representation of the sine operator ("sin").
     */
    public String getName() {
        return "sin";
    }
    /**
     * Evaluates the sine expression, either performing the sine if the operand is constant,
     * or returning a new Sin expression with the evaluated operand.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the sine operation.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = getArg().eval(vars);

        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }
}
