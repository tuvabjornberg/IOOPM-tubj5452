# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "utils.h"
# include <ctype.h>

extern char *strdup(const char *);
typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

bool not_empty(char *str) {
    return strlen(str) > 0; 
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; 
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
    int buf_siz = 25; 
    char buf[buf_siz];
    bool check_format; 
    int char_length = 0; 

    do {
        printf("%s\n", question);
        char_length = read_string(buf, buf_siz); 
        check_format = check(buf); 
        //fflush(stdin);
    } 
    while (check_format == false || char_length < 1); 

    return (answer_t) convert(buf); 

}