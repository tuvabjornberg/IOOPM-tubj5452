package org.ioopm.calculator.ast;

public class Quit extends Command {

    public Quit() {
        
    }

    public String getName() {
        return "quit"; 
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Error: Commands may not be evaluated"); 
    }
}