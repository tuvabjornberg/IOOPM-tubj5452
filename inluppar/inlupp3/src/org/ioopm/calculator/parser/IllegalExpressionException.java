package org.ioopm.calculator.parser;

public class IllegalExpressionException extends RuntimeException { //TODO: If Exception instead of RuntimeException try/catch need to be added
    public IllegalExpressionException(String msg) {
        System.out.println(msg);
    }
}
