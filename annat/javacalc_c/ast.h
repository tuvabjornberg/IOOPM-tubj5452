#pragma once

typedef struct expr expr_t; 
typedef struct constant constant_t; 
typedef struct variable variable_t; 
typedef struct addition addition_t; 

typedef expr_t *(*eval_fn)(expr_t*); 
typedef char *(*to_string_fn)(expr_t *); 
typedef void (*destroy_fn)(expr_t*); 


expr_t *eval_constant(constant_t *);
expr_t *eval_variable(variable_t *);
expr_t *eval_addition(addition_t *);

char *to_string_constant(constant_t *);
char *to_string_variable(variable_t *);
char *to_string_addition(addition_t *);

void destroy_constant(constant_t *);
void destroy_variable(variable_t *);
void destroy_addition(addition_t *);

expr_t *new_constant(int value);
expr_t *new_variable(char *name);
expr_t *new_addition(expr_t *left, expr_t *right); 