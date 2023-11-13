package org.ioopm.calculator.ast;

import java.util.HashMap;

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
}
