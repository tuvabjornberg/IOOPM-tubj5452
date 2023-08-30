# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>

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

int main(int argc, char *argv[]){
    if (argc <= 2 && is_number(argv[1])) {
        printf("%s is a number\n", argv[1]); 
    }
    else {
        if (argc <= 2) {
            printf("%s is not a number\n", argv[1]); 
        }
        else {
            printf("Please provide one command line argument!\n"); 
        }
    }
}