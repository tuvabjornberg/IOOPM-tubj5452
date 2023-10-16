typedef struct stack ioopm_stack_t; 

ioopm_stack_t *make_stack(); 

void push_stack(int i, ioopm_stack_t* s); 

int pop_stack(ioopm_stack_t *s); 

int top_stack(ioopm_stack_t *s);