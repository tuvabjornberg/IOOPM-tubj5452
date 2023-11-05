package org.ioopm.calculator.ast;
import java.lang.Math;
public class Log extends Unary {

    public Log(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "log"; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.getArg().eval(vars); 
        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue())); 
        } else {
            return new Log(arg); 
        }
    }
}