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

        if (rhs.isConstant()) {
            try {
                throw new IllegalExpressionException("Error: cannot redefine named constant");
            } catch (IllegalExpressionException e) {
                e.printStackTrace(); 
                return new Assignment(new Constant(rhs.getValue()), rhs);  //rhs; TODO: Best error handeling??
            } 
        }

        vars.put(new Variable(rhs.toString()), lhsEvaluated); 

        if (lhsEvaluated.isConstant()) {
            return new Constant(lhsEvaluated.getValue()); 
        } else {
            return lhsEvaluated; 
        }
    }
}