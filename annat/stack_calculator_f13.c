#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <ctype.h>

//returns true if a string only has digits
bool is_number(char *str)
{
    bool valid_int = true; 

    for (char *c = str; *c && valid_int; ++c)
    {
        valid_int = isdigit(*c); 
    }

    return valid_int; 
}

//reads a line from the keyboard, puts it on the heap and reurns a pointer to it
char *read_string()
{
    char *buf = NULL; 
    size_t len = 0; 
    size_t read = getline(&buf, &len, stdin); 
    buf[read-1] = '\0'; 
    return buf; 
}

void add(ioopm_stack_t *the_stack)
{
    int x = pop_stack(the_stack); 
    int y = pop_stack(the_stack); 
    push_stack(x+y, the_stack); 
}

void sub(ioopm_stack_t *the_stack)
{
    int y = pop_stack(the_stack); 
    int x = pop_stack(the_stack); 
    push_stack(x-y, the_stack); 
}

void mul(ioopm_stack_t *the_stack)
{
    int x = pop_stack(the_stack); 
    int y = pop_stack(the_stack); 
    push_stack(x*y, the_stack); 
}

void divi(ioopm_stack_t *the_stack)
{
    int y = pop_stack(the_stack); 
    int x = pop_stack(the_stack); 
    push_stack(x/y, the_stack); 
}

int main()
{
    ioopm_stack_t *the_stack = make_stack(); 
    while (true)
    {
        printf("> "); 
        char *s = read_string(); 
        if (strcmp(s, "+") == 0)
        {
            add(the_stack); 
        }
        else if (strcmp(s, "-") == 0)
        {
            sub(the_stack); 
        }
        else if (strcmp(s, "*") == 0)
        {
            mul(the_stack); 
        }
        else if (strcmp(s, "/") == 0)
        {
            divi(the_stack); 
        }
        else if (is_number(s))
        {
            push_stack(atoi(s), the_stack); 
        }
        else
        {
            printf("Invalid input"); 
        }
        printf("%d\n", top_stack(the_stack)); 
    }
}