package org.ioopm.calculator;

import java.io.IOException;
import java.util.Scanner;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import org.ioopm.calculator.visitor.*;
import java.util.List; 

/**
 * A simple calculator interface for parsing and evaluating expressions.
 * It uses the CalculatorParser for parsing input expressions and an Environment for variable storage.
 */
public class Calculator {
    private static final CalculatorParser parser = new CalculatorParser();
    private static final Environment vars = new Environment();
    private static ScopeStack stack = new ScopeStack(vars); 
    private static final EvaluationVisitor evaluator = new EvaluationVisitor();
    private static boolean functionMode = false;

    /**
     * The main method that runs the calculator interface.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        System.out.println("Welcome to the parser!");

        int expressionSuccessfulCounter = 0;
        int expressionCounter = 0;
        int fullyEvaluated = 0;

        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("Please enter an expression: ");
            String input = sc.nextLine(); 

            SymbolicExpression expression = null;
            try {
                // Parse the input expression
                expression = parser.parse(input, stack);

                if (expression.isCommand()) {
                    // Handle command expressions
                    if (expression == Vars.instance()) {
                        System.out.println(stack.getLastEnv().toString());
                    } else if (expression == Clear.instance()) {
                        stack.getLastEnv().clear();
                    } else if (expression == Quit.instance()) {
                        System.out.println("\nYou have quit the program");
                        System.out.println("Total entered expression(s): " + expressionCounter);
                        System.out.println("Successful evaluated expression(s): " + expressionSuccessfulCounter);
                        System.out.println("Expression(s) that were fully evaluated: " + fullyEvaluated);
                        break;
                    } else if (expression == End.instance()){

                        System.out.println("End can not be called outside of a function declaration");
                    }
                } else if (expression instanceof FunctionDeclaration) {
                    if (functionMode == true) {
                        System.out.println("Nested functions are not supported");
                        functionMode = false; 
                    } else {
                        functionMode = true;
                        Sequence s = (Sequence) expression.getSequence();
                        stack.getLastEnv().put(expression.getFuncName(), s);

                        while (expression != End.instance()) {
                            input = sc.nextLine(); 
                            expression = parser.parse(input, stack);
                            s.addExpression(expression);
                        }
                        functionMode = false;
                    }
                    
                } else if (expression instanceof FunctionCall) {
                    SymbolicExpression evaluated = evaluator.evaluate(expression, stack); 
                    System.out.println(evaluated);

                } else {
                    NamedConstantChecker NCchecker = new NamedConstantChecker(); 
                    boolean noIllegalAssignments = NCchecker.check(expression); 
              
                    ReassignmentChecker Rchecker = new ReassignmentChecker(stack); 
                    boolean noReassignments = Rchecker.check(expression); 

                    if (!noIllegalAssignments) {
                        List<Assignment> illegalAssignments = NCchecker.getIllegalAssignments(); 
                        
                        System.out.println("Error, assignments to named constants:");

                        for (Assignment illegal : illegalAssignments) {
                            System.out.println(illegal.toString());
                        }
                    } else if (!noReassignments) {
                        List<Variable> reassignments = Rchecker.getReassignments(); 
                        
                        System.out.println("Error, the variables are reassigned: ");
                        for (Variable re : reassignments) {
                            System.out.println(re.toString());
                        }
                    } else {
                        // Evaluate non-command expressions that passed the checks
                        SymbolicExpression evaluated = evaluator.evaluate(expression, stack); 

                        if (evaluated != null) {
                            stack.put(new Variable("ans"), evaluated); 
                            expressionSuccessfulCounter++;
                            if (evaluated.isConstant()) {
                                fullyEvaluated++;
                            }
                        }
                        System.out.println(evaluated);
                    }
                    Environment vars = stack.getLastEnv();
                    stack = new ScopeStack(vars);
                }
            } catch (SyntaxErrorException e) {
                System.out.println(e.getMessage());
            } catch (IllegalExpressionException e) {
                System.out.println(e.getMessage());
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
            finally {
                expressionCounter++;
            }      
        }
    }
}
