package org.ioopm.calculator.ast;

/**
 * A subclass of Atom, representing a variable in a symbolic expression.
 */
public class Variable extends Atom {
    private String identifier;

    /**
     * Constructs a Variable object with the given identifier.
     *
     * @param identifier The name of the variable.
     */
    public Variable(String identifier) {
        this.identifier = identifier;
    }

    /**
     * Returns the Variable object itself.
     *
     * @return The Variable object.
     */
    public Variable getVariable() {
        return this;
    }

    /**
     * Returns the string representation of the variable.
     *
     * @return The string representation of the variable.
     */
    public String toString() {
        return String.valueOf(this.identifier);
    }

    /**
     * Checks if the specified object is instance of variable, to later 
     * check equality to the current object. 
     *
     * @param other The object to compare with.
     * @return True if the objects are equal, false otherwise.
     */
    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }

    /**
     * Checks if the current variable is equal to the specified variable.
     *
     * @param other The variable to compare with.
     * @return True if the variables are equal, false otherwise.
     */
    public boolean equals(Variable other) {
        return this.identifier.equals(other.identifier);
    }

    /**
     * Evaluates the variable expression by retrieving its value from the given environment.
     * If the variable is not found in the environment, a new variable with the same identifier is returned.
     *
     * @param vars The environment containing variable values.
     * @return SymbolicExpression The result of the variable evaluation.
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression retrieved = vars.get(this.getVariable());

        if (retrieved != null) {
            return retrieved;
        } else {
            return new Variable(this.identifier);
        }
    }

    /**
     * Returns the hash code value for the variable.
     *
     * @return The hash code value for the variable.
     */
    public int hashCode() {
        return this.identifier.hashCode();
    }
}
