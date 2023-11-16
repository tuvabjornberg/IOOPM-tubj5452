package org.ioopm.calculator.ast;

import java.util.HashMap;
import java.util.Iterator;
import java.util.TreeSet;


/**
 * Represents an environment that maps variables to their corresponding
 * symbolic expressions in a hashtable. 
 */
public class Environment extends HashMap<Variable, SymbolicExpression> {

    /**
     * Default constructor for the Environment class. It inherits the constructor of HashMap.
     */
    public Environment() {
        super();
    }

    /**
     * Returns the string representation of the environment.
     *
     * @return The string representation of the environment.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: ");

        TreeSet<Variable> vars = new TreeSet<>(this.keySet());

        for (Iterator<Variable> iter = vars.iterator(); iter.hasNext(); ) {
            Variable v = iter.next();
            sb.append("\n"); 
            sb.append(v.toString());
            sb.append(" = ");
            sb.append(this.get(v).toString());
        }

        return sb.toString();
    }
}
