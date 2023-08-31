# include <stdio.h>
# include <string.h>


int string_length(char *str) {
    int length = 0; 

    while(str[length] != '\0') {
        length += 1; 
    }
    return length; 
}

void print(char *str) {
    for (int i = 0; i < string_length(str); i++) {
        putchar(str[i]); 
    }
}

void printIn(char *str) {
    for (int i = 0; i < string_length(str); i++) {
        
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s words or string", argv[0]); 
    }
    else {
        for (int i = 1; i < argc; i++) {
            int expected = strlen(argv[i]); 
            int actual = string_length(argv[i]); 
            printf("strlen(\"%s\") = %d\t\tstring_length(\"%s\") = %d\n",argv[i], expected, argv[i], actual);  
            print(argv[i]); 
            //char *my_print = print(argv[i]); 
            //printf("you wrote %s", my_print);       
            }
    }
    return 0; 
}