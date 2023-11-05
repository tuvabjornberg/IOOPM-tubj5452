package org.ioopm.calculator.ast;
import java.lang.Math;

public class Exp extends Unary {

    public Exp(SymbolicExpression argument) {
        super(argument); 
    }
    
    public String getName() {
        return "e^"; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.getArg().eval(vars); 
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue())); 
        } else {
            return new Exp(arg); 
        }
    }
}