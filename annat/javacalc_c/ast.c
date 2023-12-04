#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"

#define MAX_INT_LENGTH 12 

struct expr {
    eval_fn eval; 
    to_string_fn to_string; 
    destroy_fn destroy; 
}; 

struct constant {
    expr_t super; 
    int value; 
};

struct variable {
    expr_t super; 
    char *name; 
};

struct addition {
    expr_t super; 
    expr_t *left;
    expr_t *right;  
};

//constant
expr_t *eval_constant(constant_t *this)
{
    return new_constant(this->value); 
}

char *to_string_constant(constant_t *this)
{
    char *str = calloc(MAX_INT_LENGTH, sizeof(char)); 
    snprintf(str, MAX_INT_LENGTH, "%d", this->value);
    return str; 
}

void destroy_constant(constant_t *this)
{
    free(this); 
}

expr_t *new_constant(int value)
{
    constant_t*c = calloc(1, sizeof(constant_t)); 
    c->value = value; 
    c->super.eval = (eval_fn) eval_constant; 
    c->super.to_string = (to_string_fn) to_string_constant; 
    c->super.destroy = (destroy_fn) destroy_constant; 
    return (expr_t *) c; 
}

static bool is_constant(expr_t *e)
{
    return e->eval == (eval_fn) eval_constant; 
}

//variable
expr_t *eval_variable(variable_t *this)
{
    return new_variable(this->name); 
}

char *to_string_variable(variable_t *this)
{
    return strdup(this->name); 
}

void destroy_variable(variable_t *this)
{
    free(this->name); 
    free(this); 
}

expr_t *new_variable(char *name)
{
    variable_t *v = calloc(1, sizeof(variable_t)); 
    v->name = strdup(name); 
    v->super.eval = (eval_fn) eval_variable; 
    v->super.to_string = (to_string_fn) to_string_variable; 
    v->super.destroy = (destroy_fn) destroy_variable; 
    return (expr_t *) v; 
}

//adiition
expr_t *eval_addition(addition_t *this)
{
    expr_t *lhs = this->left->eval(this->left); 
    expr_t *rhs = this->right->eval(this->right); 
    if (is_constant(lhs) && is_constant(rhs)) 
    {
        constant_t *left = (constant_t *) lhs; 
        constant_t *right = (constant_t *) rhs; 
        int sum = left->value + right->value; 
        lhs->destroy(lhs); 
        rhs->destroy(rhs); 
        return new_constant(sum); 
    }
    else 
    {
        return new_addition(rhs, lhs); 
    }
}

char *to_string_addition(addition_t *this)
{
    char *lhs = this->left->to_string(this->left); 
    char *rhs = this->right->to_string(this->right); 
    char *str = calloc(1 + strlen(lhs) + 3 + strlen(rhs) + 1 + 1, sizeof(char)); 

    strcat(str, "(");
    strcat(str, lhs);
    strcat(str, " + ");
    strcat(str, rhs);
    strcat(str, ")");

    free(lhs); 
    free(rhs); 

    return str; 
}

void destroy_addition(addition_t *this)
{
    this->left->destroy(this->left); 
    this->right->destroy(this->right); 
    free(this); 
}

expr_t *new_addition(expr_t *left, expr_t *right)
{
    addition_t *a = calloc(1, sizeof(addition_t)); 
    a->left = left; 
    a->right = right; 
    a->super.eval = (eval_fn) eval_addition; 
    a->super.to_string = (to_string_fn) to_string_addition; 
    a->super.destroy = (destroy_fn) destroy_addition; 
    return (expr_t *) a; 
}

int main(int argc, char const *argv[]) 
{
    expr_t *e = // (2 + 3) + x
        new_addition(
            new_addition(new_constant(2), new_constant(3)), 
                new_variable("x")
        ); 

    char *input_string = e->to_string(e); 
    printf("%s\n", input_string); 

    expr_t *result = e->eval(e); // 5 + x
    char *result_string = result->to_string(result); 
    printf("%s\n", result_string); 

    free(input_string); 
    free(result_string); 
    e->destroy(e); 
    result->destroy(result); 
    
    return 0; 
}
