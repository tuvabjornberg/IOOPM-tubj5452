package org.ioopm.calculator.parser;

class SyntaxErrorException extends Exception {
    public SyntaxErrorException(String msg) {
        System.out.println(msg);
    }
}
