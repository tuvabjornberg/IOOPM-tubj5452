package org.ioopm.calculator.visitor;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.IllegalExpressionException;
import java.util.ArrayList;

/**
 * Visitor for evaluating SymbolicExpressions.
 */
public class EvaluationVisitor implements Visitor {
    private ScopeStack stack = null;


    /**
     * Evaluates a top-level SymbolicExpression within the environment.
     *
     * @param topLevel The SymbolicExpression to evaluate.
     * @param env The environment with variable assignments.
     * @return The result of the evaluation.
     */
    public SymbolicExpression evaluate(SymbolicExpression topLevel, ScopeStack stack) {
        this.stack = stack;
        return topLevel.accept(this);
    }

    /**
     * Visits an Addition node, either performing the addition if both operands are constants,
     * or returning a new Addition expression with the evaluated operands.
     *
     * @param n The Addition node to visit.
     * @return Resulting SymbolicExpression after evaluation.
    */
    @Override
    public SymbolicExpression visit(Addition n) {
        SymbolicExpression left = n.getLhs().accept(this);
        SymbolicExpression right = n.getRhs().accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }

    /**
     * Visits an Assignment node, updating the environment with the assigned variable
     * and returning the value of the assigned variable or constant. 
     * 
     * @param n The Assignment node to visit.
     * @return Resulting SymbolicExpression after evaluation.
    */
    @Override
    public SymbolicExpression visit(Assignment n) {
        SymbolicExpression lhsEvaluated = n.getLhs().accept(this);
        SymbolicExpression rhs = n.getRhs();
        
        if ((rhs.toString().toLowerCase().equals("sin") || rhs.toString().toLowerCase().equals("cos") 
            || rhs.toString().toLowerCase().equals("exp") || rhs.toString().toLowerCase().equals("quit") 
            || rhs.toString().toLowerCase().equals("clear") || rhs.toString().toLowerCase().equals("vars") 
            || rhs.toString().toLowerCase().equals("if") || rhs.toString().toLowerCase().equals("else"))) 
            {
            throw new IllegalExpressionException("Error: Right hand side is an operand");
        }
        else if (lhsEvaluated.isConstant()) {
            stack.put(new Variable(rhs.toString()), lhsEvaluated);
            return new Constant(lhsEvaluated.getValue());
        } else {
            stack.put(new Variable(rhs.toString()), lhsEvaluated);
            return lhsEvaluated;
        }
    }

    /**
     * Visits a Clear node, throwing a RuntimeException as commands may not be evaluated
     * @param n The Clear node to visit.
     * @return A RuntimeException is always thrown.
     * @throws RuntimeException Always thrown with the message "Error: Clear may not be evaluated".
    */
    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("Error: Clear may not be evaluated");
    }

    /**
    * Visits a Conditional node, evaluating the condition and returning the corresponding branch.
    *
    * @param n The Conditional node to visit.
    * @return The result of evaluating the Conditional expression.
    * @throws IllegalExpressionException If there are invalid identifiers as arguments for the Conditional.
    * @throws IllegalArgumentException If the Conditional expression contains an invalid operand.
    */
    @Override
    public SymbolicExpression visit(Conditional n) {
        SymbolicExpression lhs = n.getLhs().accept(this);
        SymbolicExpression rhs = n.getRhs().accept(this);
        boolean result = false;

        if (lhs.isConstant() && rhs.isConstant()) {
            if (n.getName().equals("==") ) {
                result = lhs.equals(rhs);

            } else if (n.getName().equals(">")) {
                result = lhs.getValue() > rhs.getValue();

            } else if (n.getName().equals("<")) {
                result = lhs.getValue() < rhs.getValue();

            } else if (n.getName().equals(">=")) {
                result = lhs.getValue() >= rhs.getValue();
        
            } else if (n.getName().equals("<=")) {
                result = lhs.getValue() <= rhs.getValue();
                
            } else {
                throw new IllegalArgumentException("Invalid operand to eval"); 
            }
        } else {
            throw new IllegalExpressionException("Invalid identifiers as arguments for conditional"); 
        }

        if (result) {
            return n.getIfBranch().accept(this); 
        } else {
            return n.getElseBranch().accept(this); 
        }
    }

    /**
     * Visists a Constant node, returning the constant itself.
     *
     * @param n The Constant node to visit. 
     * @return The constant. 
     */
    @Override
    public SymbolicExpression visit(Constant n) {
        return new Constant(n.getValue());
    }

    /**
     * Visists a cosine node, either performing the cosine if the operand is constant,
     * or returning a new Cos expression with the evaluated operand.
     *
     * @param n The Constant node to visit. 
     * @return The result of the cosine operation.  
    */
    @Override
    public SymbolicExpression visit(Cos n) {
        SymbolicExpression arg = n.getArg().accept(this);

        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }

    }

    /**
     * Visits a Division node, either performing the division if both operands are constants,
     * or returning a new Division expression.
     *
     * @param n The Division node to visit
     * @return The result of the division operation.
    */
    @Override
    public SymbolicExpression visit(Division n) {
        SymbolicExpression lhsEvaluated = n.getLhs().accept(this);
        SymbolicExpression rhsEvaluated = n.getRhs().accept(this);

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant() && rhsEvaluated.getValue() != 0) {
            double result = lhsEvaluated.getValue() / rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Division(lhsEvaluated, rhsEvaluated);
        }
    }

    /**
     * Visits an End node, throwing a RuntimeException as commands may not be evaluated
     * @param n The End node to visit.
     * @return This method always throws a RuntimeException.
     * @throws RuntimeException Always thrown with the message "Error: End may not be evaluated".
    */
    @Override
    public SymbolicExpression visit(End n) {
        throw new RuntimeException("Error: End may not be evaluated");
    }

    /**
     * Visits an exponent node, either performing the exponential operation if the argument
     * is a constant or returning an exponential expression. 
     *
     * @param n The Exp node to visit
     * @return The result of the exponential operation.
    */
    @Override
    public SymbolicExpression visit(Exp n) {
        SymbolicExpression arg = n.getArg().accept(this);

        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    @Override
    public SymbolicExpression visit(FunctionCall n){
        Variable funcName = n.getFuncName();
        ArrayList<Atom> arguments = n.getArguments();
        
        FunctionDeclaration func = (FunctionDeclaration) stack.get(funcName);
        ArrayList<Variable> parameters = func.getParameters(); 

        stack.pushEnvironment();
        for (int i = 0; i < arguments.size(); i++) {
            stack.put(parameters.get(i), arguments.get(i));
        }

        SymbolicExpression result = func.accept(this); 
        
        stack.popEnvironment();
        return result;
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        return n.getSequence().accept(this);
    }


    /**
     * Visits a logarithm node, either performing the logarithm operation if the argument
     * is a constant or returning a logarithmic expression. 
     *
     * @param n The Log node to visit. 
     * @return The result of the logarithm operation.
    */
    @Override
    public SymbolicExpression visit(Log n) {
        SymbolicExpression arg = n.getArg().accept(this);

        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }

    /**
     * Visits a Multiplication node, either performing the multiplication if both operands are constants,
     * or returning a new Multiplication expression with the evaluated operands.
     *
     * @param n The Multiplication node to visit. 
     * @return The result of the multiplication operation.
    */
    @Override
    public SymbolicExpression visit(Multiplication n) {
        SymbolicExpression lhsEvaluated = n.getLhs().accept(this); 
        SymbolicExpression rhsEvaluated = n.getRhs().accept(this); 

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() * rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Multiplication(lhsEvaluated, rhsEvaluated);
        }
    }

    /**
     * Visits a NamedConstant node, returning a new constant with the specified value.
     *
     * @param n The NamedConsatnt node to visit. 
     * @return The result of the named constant evaluation.
    */
    @Override
    public SymbolicExpression visit(NamedConstant n) {
        return new Constant(n.getValue());
    }
    
    /**
     * Visits a Negation node, returning the negative value of the expression
     *
     * @param n The Negation node to visit. 
     * @return The result of the negation operation.
    */
    @Override
    public SymbolicExpression visit(Negation n) {
        SymbolicExpression arg = n.getArg().accept(this);

        if (arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else {
            return new Negation(arg);
        }
    }

    /**
     * Visits a Quit node, throwing a RuntimeException as commands may not be evaluated
     * @param n The Quit node to visit.
     * @return This method always throws a RuntimeException.
     * @throws RuntimeException Always thrown with the message "Error: Quit may not be evaluated".
    */
    @Override
    public SymbolicExpression visit(Quit n) {
        throw new RuntimeException("Error: Quit may not be evaluated");
    }

    /**
     * Visits a Scope node, and evaluates the SymbolicExpression wihtin it
     * @param n The Scope node to visit.
     * @return the result of the evaluated scope
    */
    @Override
    public SymbolicExpression visit(Scope n) {
        stack.pushEnvironment();
        SymbolicExpression exp = n.getScope();
        SymbolicExpression result = exp.accept(this);
        stack.popEnvironment();
        return result;
    }

    public SymbolicExpression visit(Sequence n){
        SymbolicExpression result = null; 
        
        for(int i = 0; i < n.getSequenceSize(); i++) {
            result = n.accept(this); 
        }

        return result;
    } 

    /**
     * Visist a sine node, either performing the sine if the operand is constant,
     * or returning a new Sin expression with the evaluated operand.
     *
     * @param n The Sin node to visit. 
     * @return The result of the sine operation.
    */
    @Override
    public SymbolicExpression visit(Sin n) {
        SymbolicExpression arg = n.getArg().accept(this);

        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }

    }

    /**
     * Visits a Subtraction node, either performing the subtraction if both operands are constants,
     * or returning a new Subtraction expression with the evaluated operands.
     *
     * @param n The Subtraction node to visit. 
     * @return The result of the subtraction operation.
    */
    @Override
    public SymbolicExpression visit(Subtraction n) {
        SymbolicExpression lhsEvaluated = n.getLhs().accept(this); 
        SymbolicExpression rhsEvaluated = n.getRhs().accept(this); 

        if (lhsEvaluated.isConstant() && rhsEvaluated.isConstant()) {
            double result = lhsEvaluated.getValue() - rhsEvaluated.getValue();
            return new Constant(result);
        } else {
            return new Subtraction(lhsEvaluated, rhsEvaluated);
        }

    }

    /**
     * Visits a Variable node and retrieves its value from the given environment.
     * If the variable is not found in the environment, a new variable with the same identifier is returned.
     *
     * @param n The Variable node to visit. 
     * @return The result of the variable evaluation.
    */
    @Override
    public SymbolicExpression visit(Variable n) {
        SymbolicExpression retrieved = stack.get(n);
        if (retrieved != null) {
            return retrieved;
        } else {
            return n; 
        }
    }

    /**
     * Visits a Vars node, throwing a RuntimeException as commands may not be evaluated
     * @param n The Vars node to visit.
     * @return This method always throws a RuntimeException.
     * @throws RuntimeException Always thrown with the message "Error: Vars may not be evaluated".
    */
    @Override
    public SymbolicExpression visit(Vars n) {
        throw new RuntimeException("Error: Vars may not be evaluated");
    }
}
