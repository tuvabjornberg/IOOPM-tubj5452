package org.ioopm.calculator.ast;

public class Negation extends Unary {

    public Negation(SymbolicExpression argument) {
        super(argument); 
    }

    public String getName() {
        return "-"; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.getArg().eval(vars); 
        if (arg.isConstant()) {
            return new Constant(-arg.getValue()); 
        } else {
            return new Negation(arg); 
        }
    }
}