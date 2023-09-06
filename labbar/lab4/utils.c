# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h> 
# include "utils.h"

bool is_number(char *str) {
    int start = 0; 
    if (str[0] == '-') { 
        start = 1; 
    }
    for (int i = start; i < strlen(str); i++) { 
        if (!isdigit(str[i])) {
            return false; 
        }
    }
    return true; 
}

bool not_empty(char *str) {
    return strlen(str) > 0; 
}

void clear_input_buffer() {
    int c; 
    do {
        c = getchar();
    }
    while (c != '\n' && c != EOF); 
    putchar('\n'); 
}

int read_string(char *buf, int buf_siz) {
    int counter = 0;
    char c; 

    while (counter < buf_siz - 1 && (c = getchar()) != '\n') {
        buf[counter] = c;
        counter++;
    }

    buf[counter] = '\0';
    return counter;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
    int buf_siz = 255; 
    char buf[buf_siz];
    bool check_format; 
    int char_length = 0; 

    printf("%s\n", question);
    do {
        char_length = read_string(buf, buf_siz); 
        check_format = check(buf); 
        if (check(buf) == false) {
            printf("Felaktig input\n"); 
        }
    } 
    while (check_format == false || char_length < 1); 

    return convert(buf); 
}

int ask_question_int(char *question)
{
    return ask_question(question, is_number, (convert_func) atoi).int_value;
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

void print(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        putchar(str[i]); 
    }
}

void println(char *str) {
    print(str); 
    putchar('\n'); 
}