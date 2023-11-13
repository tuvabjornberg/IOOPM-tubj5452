package org.ioopm.calculator.ast;

/**
 * A subclass of Command, representing to quit. 
 */
public class Quit extends Command {
    private static final Quit theInstance = new Quit();

    /**
     * Default constructor for the Quit class.
     */
    private Quit() {}

    /**
     * Get the single instance of the Quit command.
     *
     * @return The instance of the Quit command.
     */
    public static Quit instance() {
        return theInstance;
    }

    /**
     * Returns the name of the quit operator.
     *
     * @return The string representation of quit.
     */
    public String getName() {
        return "quit"; 
    }
}