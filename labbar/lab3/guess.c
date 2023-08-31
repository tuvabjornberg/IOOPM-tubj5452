# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "utils.h"
# include <time.h>

int main(void) {
    srand(time(NULL));
    int T = rand() % 100 + 1; 
    int guess = 0; 

    char *name = ask_question_string("Skriv in ditt namn: "); 
    printf("Du '%s', jag tänkter på ett tal ... ", name);
    guess = ask_question_int("kan du gissa vilket?"); 

    for (int i = 1; i <= 16; i++) {
        if (i == 15) {
            printf("Nu har du slut på gissningar! Jag tänkte på %d", T); 
            break; 
        }
        else if (guess < T) {
            guess = ask_question_int("För litet!"); 
        }
        else if (guess > T) {
            guess = ask_question_int("För stort!"); 
        }
        else { //if (guess == T) 
            printf("Bingo!\nDet tog %s %d gissningar att komma fram till %d", name, i, T); 
            break; 
        }
    }
    return 0; 
}