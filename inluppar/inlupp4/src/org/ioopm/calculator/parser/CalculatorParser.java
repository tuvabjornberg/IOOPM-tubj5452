package org.ioopm.calculator.parser;

import org.ioopm.calculator.ast.*;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;
import java.util.*;

/**
 * Represents the parsing of strings into valid expressions defined in the AST.
 */
public class CalculatorParser {
    private StreamTokenizer st;
    private ScopeStack stack;
    private static char MULTIPLY = '*';
    private static char ADDITION = '+';
    private static char SUBTRACTION = '-';
    private static char DIVISION = '/';
    private static String NEG = "neg";
    private static char NEGATION = '-';
    private static String SIN = "sin";
    private static String COS = "cos";
    private static String LOG = "log";
    private static String EXP = "exp";
    private static char ASSIGNMENT = '=';
    private boolean functionMode = false;

    // unallowerdVars is used to check if variabel name that we
    // want to assign new meaning to is a valid name eg 3 = Quit
    // or 10 + x = L is not allowed
    private final ArrayList < String > unallowedVars = new ArrayList < String > (Arrays.asList(
        "quit", "vars", "clear", "end", 
        "cos", "sin", "exp", 
        "if", "else"));

    /**
     * Used to parse the inputted string by the Calculator program
     * @param inputString the string used to parse
     * @param vars the Environment in which the variables exist
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    public SymbolicExpression parse(String inputString, ScopeStack stack) throws IOException {
        this.st = new StreamTokenizer(new StringReader(inputString)); // reads from inputString via stringreader.
        this.stack = stack;
        this.st.ordinaryChar('-');
        this.st.ordinaryChar('/');
        this.st.eolIsSignificant(true);
        SymbolicExpression result = statement(); // calls to statement
        return result; // the final result
    }

    /**
     * Checks wether the token read is a command or an assignment
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     */
    private SymbolicExpression statement() throws IOException {
        SymbolicExpression result;
        this.st.nextToken(); //kollar på nästa token som ligger på strömmen
        if (this.st.ttype == this.st.TT_EOF) {
            throw new SyntaxErrorException("Error: Expected an expression");
        }

        if (this.st.ttype == this.st.TT_WORD) { // vilken typ det senaste tecken vi läste in hade.
            if (this.st.sval.equals("quit") || this.st.sval.equals("vars") || this.st.sval.equals("clear") || this.st.sval.equals("end")) { // sval = string Variable
                result = command();
            } else if (this.st.sval.equals("function")) {
                ArrayList<Variable> identifierList = new ArrayList<Variable>(); 
                result = function(identifierList);
            } else {
                result = assignment(); // går vidare med uttrycket.
            }
        } else {
            result = assignment(); // om inte == word, gå till assignment ändå (kan vara tt_number)
        }

        if (this.st.nextToken() != this.st.TT_EOF) { // token should be an end of stream token if we are done
            if (this.st.ttype == this.st.TT_WORD) {
                throw new SyntaxErrorException("Error: Unexpected '" + this.st.sval + "'" + " (function does not exist)");
            } else {
                throw new SyntaxErrorException("Error: Unexpected '" + String.valueOf((char) this.st.ttype) + "'");
            }
        }
        return result;
    }

    /**
    * Parses the input for function declaration and constructs a FunctionDeclaration object.
    *
    * @param identifierList An ArrayList of Variable objects representing the parameters
    *                       of the function.
    * @return A FunctionDeclaration object representing the parsed function declaration.
    * @throws IOException If there is an issue reading the next token.
    * @throws SyntaxErrorException If there are syntax errors in the function declaration,
    *         such as a missing function name, invalid parameter names, or mismatched
    *         parentheses.
    */
    private SymbolicExpression function(ArrayList<Variable> identifierList) throws IOException{
        this.st.nextToken();
        Variable functionName;
        
        if (this.st.ttype == this.st.TT_WORD){
            functionName = new Variable(this.st.sval); //creates function name as variable

            if (stack.get(functionName) instanceof FunctionDeclaration) {
                throw new SyntaxErrorException("Cannot redefine function"); 
            } else {

                this.st.nextToken(); 
                if (this.st.ttype == '(') {
                    this.st.nextToken();
                    if (this.st.ttype == this.st.TT_WORD) { //checks first parameter and adds it to an array
                        identifierList.add(new Variable((this.st.sval)));
                    } else {
                        functionMode = false; 
                        throw new SyntaxErrorException("Missing function argument(s)");
                    }

                    this.st.nextToken(); 

                    while (this.st.ttype == ',') { //checks if multiple parameters exists, adds to the same array
                        this.st.nextToken();
                        if (this.st.ttype == this.st.TT_WORD) {
                            identifierList.add(new Variable(this.st.sval));
                        } else {
                            functionMode = false; 
                            throw new SyntaxErrorException("Invalid function argument");
                        }
                        this.st.nextToken(); 
                    }

                    if (this.st.ttype != ')') {
                        functionMode = false; 
                        throw new SyntaxErrorException("expected ')' after function declaration");
                    }
                } else {
                    throw new SyntaxErrorException("Function needs at least one parameter"); 
                }
            }
        } else {
            functionMode = false; 
            throw new SyntaxErrorException("Invalid function name");
        }
        
        Sequence s = new Sequence();

        return new FunctionDeclaration(functionName, identifierList, s); 
    }

    /**
     * Checks what kind of command that should be returned
     * @return an instance of Quit, Clear or Vars depending on the token parsed
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression command() throws IOException {
        if (this.st.sval.equals("quit")) {
            return Quit.instance();
        } else if (this.st.sval.equals("clear")) {
            return Clear.instance();
        } else if (this.st.sval.equals("vars")){
            return Vars.instance();
        } else {
            return End.instance(); 
        }
    }

    /**
    * Parses and constructs a Conditional expression based on the input.
    *
    * @return A Conditional expression representing the parsed input.
    * @throws IOException If there is an issue reading the next token.
    * @throws SyntaxErrorException If the input contains an invalid operand.
    */
    private SymbolicExpression conditional() throws IOException {
        this.st.nextToken();
        SymbolicExpression lhs = expression();

        this.st.nextToken(); 
        String operator = "";
        
        if (this.st.ttype == '<' || this.st.ttype == '>' || this.st.ttype == '=') {
            operator += (char) this.st.ttype;
            this.st.nextToken(); 
            if (this.st.ttype == '=') {
                operator += "="; 
                this.st.nextToken();
            }
        } else {
            throw new SyntaxErrorException("Invalid operand"); 
        }

        SymbolicExpression rhs = expression();

        this.st.nextToken();
        SymbolicExpression ifBranch = assignment(); 

        this.st.nextToken(); 
        
        this.st.nextToken();
        SymbolicExpression elseBranch = assignment(); 
        
        return new Conditional(operator, lhs, rhs, ifBranch, elseBranch);
    }

    /**
     * Checks wether the token read is an assignment between 2 expression and 
     * descend into the right hand side of '='
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         the variable on rhs of '=' is a number or invalid variable
     */
    private SymbolicExpression assignment() throws IOException {
        SymbolicExpression result = expression();
        this.st.nextToken();

        while (this.st.ttype == ASSIGNMENT) {
            this.st.nextToken();    
            
            if (this.st.ttype == this.st.TT_NUMBER) {
                throw new SyntaxErrorException("Error: Numbers cannot be used as a variable name");
            } else if (this.st.ttype != this.st.TT_WORD) {
                throw new SyntaxErrorException("Error: Not a valid assignment of a variable"); //this handles faulty inputs after the equal sign eg. 1 = (x etc
            } else {
                if (this.st.sval.equals("ans")) {
                    throw new SyntaxErrorException("Error: ans cannot be redefined");
                }

                SymbolicExpression key = identifier();
                result = new Assignment(result, key);

            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Check if valid identifier for variable and return that if so
     * @return a SymbolicExpression that is either a named constant or a new variable
     * @throws IOException by nextToken() if it reads invalid input
     * @throws IllegalExpressionException if you try to redefine a string that isn't allowed
     */
    private SymbolicExpression identifier() throws IOException {
        SymbolicExpression result;

        if (this.unallowedVars.contains(this.st.sval)) {
            throw new IllegalExpressionException("Error: cannot redefine " + this.st.sval);
        }

        if (Constants.namedConstants.containsKey(this.st.sval)) {
            result = new NamedConstant(st.sval, Constants.namedConstants.get(st.sval));
        } else {
            result = new Variable(this.st.sval);
        }
        return result;
    }

    /**
     * Checks wether the token read is an addition or subtraction
     * and then continue on with the right hand side of operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression expression() throws IOException {
        SymbolicExpression result = term();
        this.st.nextToken();
        while (this.st.ttype == ADDITION || this.st.ttype == SUBTRACTION) {
            int operation = st.ttype;
            this.st.nextToken();
            if (operation == ADDITION) {
                result = new Addition(result, term());
            } else {
                result = new Subtraction(result, term());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is an Multiplication or
     * Division and then continue on with the right hand side of
     * operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression term() throws IOException {
        SymbolicExpression result = primary();
        this.st.nextToken();
        while (this.st.ttype == MULTIPLY || this.st.ttype == DIVISION) {
            int operation = st.ttype;
            this.st.nextToken();

            if (operation == MULTIPLY) {
                result = new Multiplication(result, primary());
            } else {
                result = new Division(result, primary());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is a parantheses and then
     * continue on with the expression inside of it or if the
     * operation is an unary operation and then continue on with
     * the right hand side of that operator else if it's a
     * number/identifier
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         missing right parantheses
     */
    private SymbolicExpression primary() throws IOException {
        SymbolicExpression result;
        if (this.st.ttype == '(') {
            this.st.nextToken();
            result = assignment();

            /// This captures unbalanced parentheses!
            if (this.st.nextToken() != ')' ) {
                throw new SyntaxErrorException("expected ')'");
            }
            
        } else if (this.st.ttype == '{') {
            this.st.nextToken(); 

            stack.pushEnvironment(); 
            result = assignment();
            stack.popEnvironment();

            result = new Scope(result); 

            /// This captures unbalanced curly brackets!
            this.st.nextToken();
            if (this.st.ttype != '}') { 
                throw new SyntaxErrorException("expected '}'");
            }
        } else if (this.st.ttype == NEGATION) {
            result = unary();
        } else if (this.st.ttype == this.st.TT_WORD) {
            if (st.sval.equals(SIN) ||
                st.sval.equals(COS) ||
                st.sval.equals(EXP) ||
                st.sval.equals(NEG) ||
                st.sval.equals(LOG)) {

                result = unary();
        
            } else if (this.st.sval.equals("if")) {
                result = conditional(); // går vidare med conditional 
            } else {
                result = identifier();

                if (stack.get(result) != null && stack.get(result) instanceof FunctionDeclaration) {
                    this.st.nextToken(); 

                    Variable funcName;
                    if (result instanceof Variable) {
                        funcName = (Variable) result;                         
                    } else {    
                        throw new SyntaxErrorException("Invalid combination of func name and '(");
                    }

                    ArrayList<Atom> identifierList = new ArrayList<>(); 

                    this.st.nextToken();

                    if (this.st.ttype == this.st.TT_WORD) { //checks first parameter and adds it to an array
                        identifierList.add((Atom) identifier());
                    } else if (this.st.ttype == this.st.TT_NUMBER){
                        identifierList.add(new Constant((this.st.nval)));
                    } else {
                        throw new SyntaxErrorException("Invalid input to function"); 
                    }
  
                    this.st.nextToken(); 

                    while (this.st.ttype == ',') { //checks if multiple parameters exists and adds to the same array
                        this.st.nextToken();
                        if (this.st.ttype == this.st.TT_WORD) {
                            identifierList.add((Atom) identifier());
                        } else if (this.st.ttype == this.st.TT_NUMBER){
                            identifierList.add(new Constant((this.st.nval)));
                        } else {
                            throw new SyntaxErrorException("Invalid function argument");
                        }
                        this.st.nextToken(); 
                    }  
                    
                    FunctionDeclaration func = (FunctionDeclaration) stack.get(funcName);

                    int paramSize = func.getParameters().size(); 
                    int argSize = identifierList.size(); 

                    if (paramSize != argSize){
                        throw new IllegalExpressionException("Error: Function '" + funcName +
                                "' called with the wrong number of arguments. Expected " +
                                paramSize + ", got " + argSize);               
                    } else {
                        result = new FunctionCall(funcName, identifierList); 
                    }
                } 
            }
        } else {
            this.st.pushBack();
            result = number();
        }
        return result;
    }

    /**
     * Checks what type of Unary operation the token read is and
     * then continues with the expression that the operator holds
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression unary() throws IOException {
        SymbolicExpression result;
        int operationNeg = st.ttype;
        String operation = st.sval;
        this.st.nextToken();
        if (operationNeg == NEGATION || operation.equals(NEG)) {
            result = new Negation(primary());
        } else if (operation.equals(SIN)) {
            result = new Sin(primary());
        } else if (operation.equals(COS)) {
            result = new Cos(primary());
        } else if (operation.equals(LOG)) {
            result = new Log(primary());
        } else {
            result = new Exp(primary());
        }
        return result;
    }

    /**
     * Checks if the token read is a number - should always be a number in this method
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         expected a number which is not present
     */
    private SymbolicExpression number() throws IOException {
        this.st.nextToken();
        if (this.st.ttype == this.st.TT_NUMBER) {
            return new Constant(this.st.nval);
        } else {
            throw new SyntaxErrorException("Error: Expected number");
        }
    }
}
