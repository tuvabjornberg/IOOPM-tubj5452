package org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression operand) {
        super(operand); 
    }

    public String getName() {
        return "log"; 
    }
}