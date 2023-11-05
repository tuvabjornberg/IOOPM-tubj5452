package org.ioopm.calculator.ast;
import java.lang.Math;
public class Cos extends Unary {

    public Cos(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "cos"; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.getArg().eval(vars); 
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue())); 
        } else {
            return new Cos(arg); 
        }
    }
}