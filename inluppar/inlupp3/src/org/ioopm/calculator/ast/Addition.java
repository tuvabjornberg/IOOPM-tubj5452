package org.ioopm.calculator.ast;

public class Addition extends Binary {

    public Addition(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs); 
    }

    public String getName() {
        return "+"; 
    }

    public int getPriority() {
        return 50; 
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhsEvaluated = this.getLhs().eval(vars); 
        SymbolicExpression rhsEvaluated = this.getRhs().eval(vars); 
        
        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() + rhsEvaluated.getValue(); 
            return new Constant(result); 
        } else {
            return new Addition(lhsEvaluated, rhsEvaluated); 
        }
    }
}