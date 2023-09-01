# include <stdio.h>
# include <stdbool.h>
# include "utils.h"

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
    return (item_t) {.name = name, .description = description, .price = price, .shelf = shelf}; 
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

item_t input_item(void) {
    char *name = ask_question_string("Skriv in varans namn: "); 
    char *description = ask_question_string("Skriv in en kort beskrivning: "); 
    int price = ask_question_int("Skriv in varans pris i ören: "); 
    char *shelf = ask_question_shelf("Skriv in hyllan: "); 

}

int main(void) {
    item_t ex = { .name = "Hammare", .description = "För att slå", .price = 40, .shelf = "A25"}; 
    print_item(&ex); 
}