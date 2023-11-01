package org.ioopm.calculator.parser;

public class IllegalExpressionException extends Exception {
    public IllegalExpressionException(String msg) {
        System.out.println(msg);
    }
}
