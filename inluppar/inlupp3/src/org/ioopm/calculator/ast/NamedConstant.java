package org.ioopm.calculator.ast;

/**
 * A subclass of Atom, representing a named constant with a specific value in a symbolic expression.
 */
public class NamedConstant extends Atom {
    private String name;
    private double value;

    /**
     * Constructs a NamedConstant object with the given name and numeric value.
     *
     * @param name  The name of the constant.
     * @param value The numeric value of the constant.
     */
    public NamedConstant(String name, double value) {
        this.name = name;
        this.value = value;
    }

    /**
     * Returns true, indicating that the object is a constant.
     *
     * @return True.
     */
    public boolean isConstant() {
        return true;
    }

    /**
     * Returns the name of the constant as a string representation.
     *
     * @return The string representation of the named constant.
     */
    public String toString() {
        return this.name;
    }

    /**
     * Returns the numeric value of the named constant.
     *
     * @return The numeric value of the named constant.
     */
    public double getValue() {
        return this.value;
    }

    /**
     * Evaluates the named constant expression by returning a new constant with the specified value.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the named constant evaluation.
     */
    public SymbolicExpression eval(Environment vars) {
        return new Constant(this.value);
    }
}
