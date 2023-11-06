package org.ioopm.calculator.ast;

public class IllegalExpressionException extends Exception {
    public IllegalExpressionException(String msg) {
        System.out.println(msg);
    }
}
