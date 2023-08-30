# include <stdio.h>
# include <stdlib.h>
# include <math.h>
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
    int a = atoi(argv[1]); 
    int b = atoi(argv[2]); 

    if (argc != 3 || !is_number(argv[1]) || !is_number(argv[2]) || a < 0 || b < 0) {
        printf("Invalid argument(s)"); 
    }
    else {
        while (a != b) {
            if (a < b) {
                b = b - a; 
            }
            else if (a > b) {
                a = a - b; 
            }
        }
        printf("%d", a); 
    }
}