package org.ioopm.calculator.ast;

import java.util.HashMap;

/**
 * A collection of named constants with their respective values.
 * These constants can be accessed statically without creating an instance of the class.
 */
public class Constants {
    
    /**
     * A map containing named constants and their corresponding numeric values.
     */
    public static final HashMap<String, Double> namedConstants = new HashMap<>();

    /**
     * Initializes the named constants map with commonly used constants and their values.
     */
    static {
        Constants.namedConstants.put("pi", Math.PI);
        Constants.namedConstants.put("e", Math.E);
        Constants.namedConstants.put("Answer", 42.0);
        Constants.namedConstants.put("L", 6.022140857 * Math.pow(10, 23));
    }
}
