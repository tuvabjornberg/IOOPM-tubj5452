package org.ioopm.calculator;

import java.io.IOException;
import java.util.Map;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

/**
 * A simple calculator interface for parsing and evaluating expressions.
 * It uses the CalculatorParser for parsing input expressions and an Environment for variable storage.
 */
public class Calculator {
    private static final CalculatorParser parser = new CalculatorParser();
    private static final Environment vars = new Environment();

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

        while (true) {
            System.out.println("Please enter an expression: ");
            String input = System.console().readLine();

            SymbolicExpression expression = null;
            try {
                // Parse the input expression
                expression = parser.parse(input, vars);

                if (expression.isCommand()) {
                    // Handle command expressions
                    if (expression == Vars.instance()) {
                        for (Map.Entry<Variable, SymbolicExpression> set : vars.entrySet()) {
                            System.out.println(set.getKey() + " = " + set.getValue());
                        }
                    } else if (expression == Clear.instance()) {
                        vars.clear();
                    } else if (expression == Quit.instance()) {
                        System.out.println("\nYou have quit the program");
                        System.out.println("Total entered expression(s): " + expressionCounter);
                        System.out.println("Successful evaluated expression(s): " + expressionSuccessfulCounter);
                        System.out.println("Expression(s) that were fully evaluated: " + fullyEvaluated);
                        break;
                    } else {
                        throw new SyntaxErrorException("Invalid command operation");
                    }
                } else {
                    // Evaluate non-command expressions
                    SymbolicExpression evaluated = expression.eval(vars);

                    if (evaluated != null) {
                        expressionSuccessfulCounter++;
                        if (evaluated.isConstant()) {
                            fullyEvaluated++;
                        }
                    }

                    System.out.println(evaluated);
                }

            } catch (SyntaxErrorException e) {
                System.out.println(e.getMessage());
            } catch (IllegalExpressionException e) {
                System.out.println(e.getMessage());
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }

            expressionCounter++;
        }

    }
}
