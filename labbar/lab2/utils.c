# include <stdio.h>
# include <string.h>

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

char ask_question_string(char *question) {

}

int read_string(char *buf, int buf_siz) {
    int real_size = 0; 
    for (int i = 0; i < strlen(buf); i++) {
        real_size = i; 
    }
    return buf_siz - real_size; 
}

int main(void) {
    int number; 

    number = ask_question_int("First number: "); 
    printf("You wrote '%d'\n", number); 

    number = ask_question_int("Second number: "); 
    printf("You wrote '%d'\n", number); 

    return 0; 
}