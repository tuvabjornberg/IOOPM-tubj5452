package org.ioopm.calculator.ast;

public class Assignment extends Binary {

    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs); 
    }

    public String getName() {
        return "="; 
    }

    public int getPriority() {
        return 0; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars); 
        SymbolicExpression rhs = this.getRhs(); 

        vars.put(new Variable(rhs.toString()), lhsEvaluated); 

        if (lhsEvaluated.isConstant()) {
            return new Constant(lhsEvaluated.getValue()); 
        } else {
            return lhsEvaluated; 
        }
    }
}