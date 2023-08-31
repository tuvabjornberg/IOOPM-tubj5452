# include <stdio.h>
# include <string.h>
# include "utils.h"

void clear_input_buffer() {
    int c; 
    do {
        c = getchar();
    }
    while (c != '\n' && c != EOF); 
    putchar('\n'); 
}

int ask_question_int(char *question) {
    int result = 0;
    int conversions = 0; 

    do {
        printf("%s\n", question); 
        conversions = scanf("%d", &result); 
        clear_input_buffer(); 
    } 
    while (conversions < 1); 

    return result; 
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

char *ask_question_string(char *question, char *buf, int buf_siz) {
    int conversions = 0; 
    int result = 0; 

    do {
        printf("%s\n", question);
        result = read_string(buf, buf_siz); 
        if (result != 0) { 
            conversions = 1;
        }
        fflush(stdin);
    } 
    while (conversions < 1); 

    return buf; 
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