package org.ioopm.calculator;

import java.io.IOException;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import org.ioopm.calculator.visitor.*;
import java.util.*; 

/**
 * A simple calculator interface for parsing and evaluating expressions.
 * It uses the CalculatorParser for parsing input expressions and a ScopeStack for variable storage.
 */
public class Calculator {
    private static final CalculatorParser parser = new CalculatorParser();
    private static final Environment vars = new Environment();
    private static final EvaluationVisitor evaluator = new EvaluationVisitor();
    private static ScopeStack stack = new ScopeStack(vars); 
    
    private static boolean functionMode = false;
    private static Boolean emptyBody = true; 
    private static int expressionCounter = 0; 
    private static int expressionSuccessfulCounter = 0; 
    private static int fullyEvaluated = 0; 
    private static Variable funcName = null; 

    /**
    * Evaluates and performs actions based on command expressions.
    *
    * @param expression The command expression to be evaluated.
    * @return The command expression.
    */
    public static SymbolicExpression evalCommand(SymbolicExpression expression) {
        if (expression == Vars.instance()) {
            System.out.println(stack.getLastEnv().toString());
        } else if (expression == Clear.instance()) {
            stack.getLastEnv().clear();
        } else if (expression == Quit.instance()) {
            System.out.println("\nYou have quit the program");
            System.out.println("Total entered expression(s): " + expressionCounter);
            System.out.println("Successful evaluated expression(s): " + expressionSuccessfulCounter);
            System.out.println("Expression(s) that were fully evaluated: " + fullyEvaluated);
        } else {
            System.out.println("End can not be called outside of a function declaration");
        }
        return expression; 
    }

    /**
    * Checks if the right-hand side of an assignment in a function conflicts with function parameters.
    *
    * @param expression The assignment expression to be checked.
    * @param funcParam The list of parameters of the function.
    * @return True if the assignment is valid, false otherwise.
    */
    public static boolean rhsAssignesParamCheck(SymbolicExpression expression, ArrayList<Variable> funcParam) {
        SymbolicExpression lhs = ((Assignment)expression).getLhs();
        if (lhs instanceof Constant) {
            SymbolicExpression rhs = ((Assignment)expression).getRhs();
            if (funcParam.contains(rhs)) {
                System.out.println("Assignment in function can not have the same name as param");
                stack.getLastEnv().remove(funcName);
                emptyBody = false; 
                return true; 
            }
        }
        return false; 
    }

    /**
    * Evaluates and processes a function declaration, adding it to the environment.
    *
    * @param expression The function declaration expression to be evaluated.
    * @param input The original input line containing the function declaration.
    * @param sc The Scanner object for user input.
    * @throws IOException If an I/O error occurs during function body parsing.
    */
    public static void evalFunctionDeclaration(SymbolicExpression expression, String input, Scanner sc) throws IOException {
        functionMode = true;
        emptyBody = true; 

        FunctionDeclaration fdExpression = expression.getFunctionDeclaration(); 

        funcName = expression.getFuncName(); 
        ArrayList<Variable> funcParam = expression.getParameters();

        stack.getLastEnv().put(funcName, fdExpression);

        while (functionMode) {
            input = sc.nextLine(); 
            expression = parser.parse(input, stack);    
            
            if (expression instanceof Assignment && rhsAssignesParamCheck(expression, funcParam)){
                break; 
            } 

            if (expression instanceof FunctionDeclaration) {
                System.out.println("Nested functions are not allowed");
                stack.getLastEnv().remove(funcName);
                break; 
            }

            if (expression != End.instance()) {
                emptyBody = false; 
                fdExpression.getSequence().addExpression(expression); 
            } else {
                functionMode = false; 
            }
        }

        if (emptyBody) {
            System.out.println("Function body cannot be empty");
            stack.getLastEnv().remove(funcName);
        }
        
        expressionSuccessfulCounter++;             
    }

    /**
    * Evaluates a function call, replacing the call with the body of the function and performing the evaluation.
    *
    * @param expression The function call expression to be evaluated.
    */
    public static void evalFunctionCall(SymbolicExpression expression) {
        SymbolicExpression evaluated = evaluator.evaluate(expression, stack); 
                    
        expressionSuccessfulCounter++;
        if (evaluated != null) {
            if (evaluated.isConstant()) {
                fullyEvaluated++;
            }

            System.out.println(evaluated);
        }
    }

    /**
    * Checks for illegal assignments to named constants.
    *
    * @param expression The expression to be checked for named constant assignments.
    * @return True if no illegal assignments, false otherwise.
    */
    public static boolean namedConstantCheck(SymbolicExpression expression) {
        NamedConstantChecker NCchecker = new NamedConstantChecker(); 
        boolean noIllegalAssignments = NCchecker.check(expression); 

        if (!noIllegalAssignments) {
            List<Assignment> illegalAssignments = NCchecker.getIllegalAssignments(); 
            
            System.out.println("Error, assignments to named constants:");
            for (Assignment illegal : illegalAssignments) {
                System.out.println(illegal.toString());
            }
        }

        return noIllegalAssignments; 
    }

    /**
    * Checks for variable reassignments in the expression.
    *
    * @param expression The expression to be checked for variable reassignments.
    * @return True if no variable reassignments, false otherwise.
    */
    public static boolean reassignmentCheck(SymbolicExpression expression) {
        ReassignmentChecker Rchecker = new ReassignmentChecker(stack); 
        boolean noReassignments = Rchecker.check(expression); 

        if (!noReassignments) {
            List<Variable> reassignments = Rchecker.getReassignments(); 
            
            System.out.println("Error, the variables are reassigned: ");
            for (Variable re : reassignments) {
                System.out.println(re.toString());
            }
        }
        return noReassignments; 
    }

    /**
    * Evaluates and prints the result of a non-command expression.
    *
    * @param expression The expression to be evaluated.
    */
    public static void evalExpression(SymbolicExpression expression) {
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

    /**
     * The main method that runs the calculator interface.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        System.out.println("Welcome to the parser!");

        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("Please enter an expression: ");
            String input = sc.nextLine(); 

            SymbolicExpression expression = null;
            try {
                // Parse the input expression
                expression = parser.parse(input, stack);

                if (expression.isCommand()) {
                    // Handles command inputs
                    if (evalCommand(expression) instanceof Quit) {
                        break; 
                    }
 
                } else if (expression instanceof FunctionDeclaration) {
                    evalFunctionDeclaration(expression, input, sc);
                    
                } else if (expression instanceof FunctionCall) {
                    evalFunctionCall(expression);

                } else {
                    if (namedConstantCheck(expression) && reassignmentCheck(expression)) {
                        // Evaluate non-command expressions that passed the checks
                        evalExpression(expression);
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
                // If an exceptions was thrown during parsing of the function body we remove it from the environment
                if (functionMode) { 
                    functionMode = false; 
                    stack.getLastEnv().remove(funcName);
                }
                expressionCounter++;
            }      
        }
    }
}
