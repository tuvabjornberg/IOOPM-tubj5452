package org.ioopm.calculator.ast;

public class Clear extends Command{
    private static final Clear theInstance = new Clear();

    private Clear() {}

    public static Clear instance() {
        return theInstance;
    }

    public String getName() {
        return "clear"; 
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Error: Commands may not be evaluated"); 
    }

    public boolean isCommand() {
        return true; 
    }
}
