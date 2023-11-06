package org.ioopm.calculator.parser;

class SyntaxErrorException extends RuntimeException { //TODO: If Exception instead of RuntimeException try/catch need to be added
    public SyntaxErrorException(String msg) {
        System.out.println(msg);
    }
}
