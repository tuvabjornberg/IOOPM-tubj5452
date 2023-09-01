# include <stdio.h>
# include <ctype.h>
# include <string.h> 

void print(char *str) {
    for (; *str != '\0'; ++str) {
        putchar(*str); 
    }
}

int main(void) {
    char *prompt = "Hejhallå"; 
    print(prompt); 
}