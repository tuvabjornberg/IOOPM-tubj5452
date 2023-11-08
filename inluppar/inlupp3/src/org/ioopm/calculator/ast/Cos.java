package org.ioopm.calculator.ast;

/**
 * A subclass of Unary, representing the cos operation.
 */
public class Cos extends Unary {

    /**
     * Constructs a Cos object with the given operand.
     *
     * @param argument The operand of the cosine operation.
     */
    public Cos(SymbolicExpression argument) {
        super(argument);
    }

    /**
     * Returns the name of the cosine operator.
     *
     * @return The string representation of the cosine operator ("cos").
     */
    @Override
    public String getName() {
        return "cos";
    }

    /**
     * Evaluates the cosine expression, either performing the cosine if the operand is constant,
     * or returning a new Cos expression with the evaluated operand.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the cosine operation.
     */
    @Override
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.getArg().eval(vars);

        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }
}
