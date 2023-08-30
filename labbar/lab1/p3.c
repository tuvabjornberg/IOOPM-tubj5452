# include <stdio.h>
# include <string.h>

int main(void){
    int total = 0; 
    for (int i = 1; i <= 10; i++) {
        for (int N = 1; N <= i; N++) {
            printf("%s", "*"); 
            total += 1; 
        }
        printf("\n"); 
    }
    printf("Totalt: %d", total); 
}