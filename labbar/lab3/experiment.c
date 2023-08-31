# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../lab2/utils.h"

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef char(*check_func)(char, bool); 
typedef char(*convert_func)(char, answer_t);


bool not_empty(char *str) {
    return strlen(str) > 0; 
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
    int conversions = 0; 
    answer_t result; 
    char c; 

    do {
        printf("%s\n", question);
        result = read_string(buf, buf_siz); 
        if (c.) { 
            conversions = 1;
        }
        fflush(stdin);
    } 
    while (conversions < 1 && (c = getchar()) != '\n'); 

    return buf; 
}




int main(void) {
    int buf_siz = 25; 
    char buf[buf_siz];

    answer_t answer = ask_question("Write a string: ", buf, buf_siz); 
    printf("You wrote: '%s' (%zu tecken)\n", buf, strlen(str)); 




    return 0; 
}