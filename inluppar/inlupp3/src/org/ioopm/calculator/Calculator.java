package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

public class Calculator {
    private CalculatorParser parser; 
    private Environment vars; 
    public static void main(String[] args)
    {

        while (true) {
            String input = System.console().readLine(); 
            SymbolicExpression expression = parser.parse(input, vars);

            if (expression.isCommand()) {
                Command command = (Command) expression; 
                if (command.instance() == "vars") {
                    System.out.println(vars);
                } else if (command.instance == "clear") {
                    vars.clear; 
                } else if (command.instance == "quit") {
                    System.out.println("You have quit");
                    return; 
                } else {}


            }
            expression.eval(vars); 
        }

    }
}