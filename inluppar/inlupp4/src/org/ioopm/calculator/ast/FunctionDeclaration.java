package org.ioopm.calculator.ast;

import java.util.ArrayList; 

public class FunctionDeclaration extends SymbolicExpression {
    private String functionName; 
    private ArrayList<Variable> parameters; 
    private Sequence body; 

    public FunctionDeclaration(String functionName, ArrayList<Variable> parameters, Sequence body){
        this.functionName = functionName;
        this.parameters = parameters;
        this.body = body;    
    }

    public String getFunctionName() {
        return this.functionName;
    }
    
    public Sequence getSequence() {
        return this.body; 
    }

    
}
