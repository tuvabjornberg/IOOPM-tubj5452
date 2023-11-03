package org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "log"; 
    }
}