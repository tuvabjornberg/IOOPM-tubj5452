package org.ioopm.calculator.ast;

public class Quit extends Command {
    private static final Quit theInstance = new Quit();

    private Quit() {}

    public static Quit instance() {
        return theInstance;
    }

    public String getName() {
        return "quit"; 
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Error: Commands may not be evaluated"); 
    }

    public boolean isCommand() {
        return true; 
    }
}