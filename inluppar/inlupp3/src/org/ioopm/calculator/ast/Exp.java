package org.ioopm.calculator.ast;

import java.lang.Math;

/**
 * A subclass of Unary, representing the exponential (e^x) operation.
 */
public class Exp extends Unary {

    /**
     * Constructs an Exp object with the given operand.
     *
     * @param argument The operand of the exponential operation.
     */
    public Exp(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the exponential operator.
     *
     * @return The string representation of the exponential operator ("e^").
     */
    public String getName() {
        return "e^";
    }

    /**
     * Evaluates the exponential expression.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the exponential operation.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = getArg().eval(vars);

        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }
}
