package org.ioopm.calculator.ast;

/**
 * A subclass of Unary, representing logarithm (log) operation.
 */
public class Log extends Unary {

    /**
     * Constructs a Log object with the given operand.
     *
     * @param argument The operand of the logarithm operation.
     */
    public Log(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the logarithm operator.
     *
     * @return The string representation of the logarithm operator ("log").
     */
    @Override
    public String getName() {
        return "log";
    }

    /**
     * Evaluates the logarithm expression.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the logarithm operation.
     */
    @Override
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = getArg().eval(vars);

        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }
}
