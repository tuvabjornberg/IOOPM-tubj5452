package org.ioopm.calculator.ast;

import org.ioopm.calculator.visitor.*;
import java.util.Deque;
import java.util.ArrayDeque;

public class ScopeStack extends Environment {
    Deque<Environment> stack;

    /**
     * Constructs a stack of enviornments
     */
    public ScopeStack(Environment env){
        super();
        this.stack = new ArrayDeque<>();
        this.stack.push(new Environment());
    }

    /**
     * Returns the variable if it exists in the stack scope
     *
     * @param k The variable to look for
     * @return returns the variable from correct scope
     */
    @Override
    public SymbolicExpression get(Object k){

        for (Environment env: this.stack) {
            if (env.containsKey(k)) {
                return env.get(k);
            } 
        }
         
        return super.get(k);
    }

    /**
     * Puts the input variable into the current scope
     *
     * @param v The variable to insert
     * @param value The symbolic expression of the variable to insert
     * @return returns the symbolic expression inserted
     */
    @Override
    public SymbolicExpression put(Variable v, SymbolicExpression value){
        Environment env = this.stack.getFirst();
        return env.put(v, value);
    }

    /**                             
     * Pushes the given environment to the stack
     */
    public void pushEnvironment(){
        this.stack.addFirst(new Environment());
    }

    /**
     * Pops the top environment from the stack
     */
    public void popEnvironment(){
        this.stack.removeFirst();
    }

}
