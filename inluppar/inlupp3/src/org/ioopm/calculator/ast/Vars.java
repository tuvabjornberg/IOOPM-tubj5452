package org.ioopm.calculator.ast;

public class Vars extends Command {

    public Vars() {
        
    }

    public String getName() {
        return "vars"; 
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Error: Commands may not be evaluated"); 
    }
}