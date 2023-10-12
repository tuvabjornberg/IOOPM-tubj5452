#include "stack.h"
#include <stdlib.h>

struct stack
{
    int entry[4]; 
};

ioopm_stack_t *make_stack()
{
    return calloc(1, sizeof(ioopm_stack_t)); 
}


void push_stack(int i, ioopm_stack_t* s)
{
    for (int k = 0; k < 3; k++)
    {
        s->entry[k + 1] = s->entry[k]; 
    }
    s->entry[0] = i; 
}

int pop_stack(ioopm_stack_t *s)
{
    int old_top = s->entry[0]; 
    for (int k = 0; k < 3; k++)
    {
        s->entry[k] = s->entry[k + 1]; 
    }
    return old_top; 
}

int top_stack(ioopm_stack_t *s)
{
    return s->entry[0]; 
}