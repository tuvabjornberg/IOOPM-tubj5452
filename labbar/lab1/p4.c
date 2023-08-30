# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 2 || argc > 3) {
        printf("ERROR: invalid arguments, should be two ints"); 
    }
    else {
        int total = 0; 
        int rows = atoi(argv[1]); 
        int start = atoi(argv[2]); 

        for (int i = 0; i <= rows; i++) {
            for (int N = 1; N <= start * i; N++) {
                printf("%s", "*"); 
                total += 1; 
            }
            printf("\n"); 
        }
        printf("Totalt: %d", total); 
    }
}