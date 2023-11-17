package org.ioopm.calculator.visitor;

import org.ioopm.calculator.ast.*;
import java.util.ArrayList;
import java.util.List;

public class NamedConstantChecker implements Visitor {
    private List<Assignment> illegalAssignments;

    public NamedConstantChecker() {
        this.illegalAssignments = new ArrayList<>();
    }

    public List<Assignment> getIllegalAssignments() {
        return illegalAssignments;
    }

    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this);
        return this.illegalAssignments.isEmpty(); 
    }

    public SymbolicExpression visit(Addition a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        return null;
    }

    public SymbolicExpression visit(Assignment a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        if (a.getRhs().isConstant()) {
            illegalAssignments.add(a);
        }
        return null;
    }

    public SymbolicExpression visit(Clear a) {
        return null; 
    }

    public SymbolicExpression visit(Constant a) {
        return null; 
    }

    public SymbolicExpression visit(Cos a) {
        a.getArg().accept(this); 
        return null; 
    }

    public SymbolicExpression visit(Division a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        return null;
    }

    public SymbolicExpression visit(Exp a) {
        a.getArg().accept(this); 
        return null;
    }

    public SymbolicExpression visit(Log a) {
        a.getArg().accept(this); 
        return null;
    }

    public SymbolicExpression visit(Multiplication a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        return null;
    }

    public SymbolicExpression visit(NamedConstant a) {
        return null; //TODO: ??????
    }

    public SymbolicExpression visit(Negation a) {
        a.getArg().accept(this); 
        return null;
    }

    public SymbolicExpression visit(Quit a) {
        return null; 
    }

    public SymbolicExpression visit(Sin a) {
        a.getArg().accept(this); 
        return null;
    }

    public SymbolicExpression visit(Subtraction a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        return null;
    }

    public SymbolicExpression visit(Variable a) {
        return null; 
    }

    public SymbolicExpression visit(Vars a) {
        return null; 
    }


}