# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "utils.h"
# include <string.h>
# include <ctype.h>
# include <time.h>

typedef struct item {
    char *name; 
    char *description; 
    int price; 
    char *shelf; 
} item_t;

void print_item(item_t *item) {
    printf("Name: %s\nDesc: %s\nPrice: %d\nShelf: %s\n", 
        item->name, item->description, (item->price) % 100, item->shelf);
}

item_t make_item(char *name, char *description, int price, char *shelf) {
    return (item_t) {name, description, price, shelf}; 
}

bool check_shelf(char *shelf) {
    if (isalpha(shelf[0]) && !islower(shelf[0]) && (strlen(shelf) > 1) && is_number(++shelf)) {
        return true; 
    }
    else {
        return false;
    }
}

char *ask_question_shelf(char *question) {
    char *shelf;

    do {
        shelf = ask_question_string(question);
    }
    while (!check_shelf(shelf)); 

    return shelf;
}

item_t input_item(void) {
    char *name = ask_question_string("Skriv in varans namn: "); 
    char *description = ask_question_string("Skriv in en kort beskrivning: "); 
    int price = ask_question_int("Skriv in varans pris i ören: "); 
    char *shelf = ask_question_shelf("Skriv in hyllan: (På formatet 'A10')"); 

    return (item_t) {name, description, price, shelf}; 
}

char *magick(char **array1, char **array2, char **array3, int size) {
    char buf[255]; 
    int j = 0; 

    int rand_index1 = rand() % size; 
    int rand_index2 = rand() % size; 
    int rand_index3 = rand() % size; 


    for(char *i = array1[rand_index1]; *i != '\0'; i++) {
        buf[j++] = *i; 
    }

    buf[j++] = '-'; 

    for(char *i = array2[rand_index2]; *i != '\0'; i++) {
        buf[j++] = *i; 
    }

    buf[j++] = ' '; 

    for(char *i = array3[rand_index3]; *i != '\0'; i++) {
        buf[j++] = *i; 
    }
    
    buf[j++] = '\0'; 

    return strdup(buf); 

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    //item_t ex = { .name = "Hammare", .description = "För att slå", .price = 40, .shelf = "A25"}; 
    //print_item(&ex); 
    //input_item(); 

    char *array1[] = { "Laser", "Polka", "Extra" }; // TODO: Lägg till!
    char *array2[] = { "Förnicklad", "Smakande", "Ordinär" }; // TODO: Lägg till!
    char *array3[] = { "Skruvdragare", "Kola", "Uppgift" }; // TODO: Lägg till!
    //char *array4[] = { "Småspik", "Hammare", "Tejp"}; 
    //char *array5[] = { "Tumstock", "Träplanka", "Kruka"}; 

    if (argc < 2) {
        printf("Usage: %s number\n", argv[0]);
    }
    else {
        item_t db[16]; // Array med plats för 16 varor
        int db_siz = 0; // Antalet varor i arrayen just nu

        int items = atoi(argv[1]); // Antalet varor som skall skapas

        if (items > 0 && items <= 16) {
            for (int i = 0; i < items; ++i)
        {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
        }
    }
    else {
        puts("Sorry, must have [1-16] items in database.");
        return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i) {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = rand() % 200000;
        char shelf[] = { rand() % ('Z'-'A') + 'A',
                         rand() % 10 + '0',
                         rand() % 10 + '0',
                         '\0' };
                         printf("\n%s\n", shelf); 
        item_t item = make_item(name, desc, price, shelf);
                                 printf("\n%s\n", shelf); 


        db[db_siz] = item;
                printf("before ++: %d\n", db_siz); 
                printf("db[db_siz].shelf: %s\n", db[0].shelf); 
                 printf("db[db_siz].shelf: %s\n", db[1].shelf); 
                 printf("db[db_siz].shelf: %s\n", db[1].shelf); 

                 printf("db[db_siz].shelf: %s\n", db[db_siz].shelf); 
               

        ++db_siz;
        printf("after ++; %d\n", db_siz); 
    }
                     printf("db[db_siz].shelf: %s\n", db[db_siz-2].shelf); 


     // Skriv ut innehållet
    for (int i = 0; i < db_siz; ++i)
    {
        print_item(&db[i]);
    }
    }
    return 0;
}