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
    printf("Name: %s\nDesc: %s\nPrice: %d.%d\nShelf: %s\n", 
        item->name, item->description, item->price / 100, item->price % 100 , item->shelf);
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

    return make_item(name, description, price, shelf); 
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

void print_menu(void) {
    printf("\n[L]ägga till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[A]vsluta\n"); 

}

char ask_question_menu(void) {
    print_menu(); 
    char *user_input = ask_question_string("");
    int valid_user_input = 0; 

    do {
        switch (toupper(*user_input)) {
            case 'L':
            case 'T': 
            case 'R': 
            case 'G': 
            case 'H': 
            case 'A': 
                valid_user_input = 1; 
                break;
            default:
                user_input = ask_question_string("Försök igen\n");
            } 
    }
    while(!valid_user_input); 

    return toupper(*user_input);
}

void list_db(item_t *items, int no_items) {
    for (int i = 0; i < no_items; i++) {
        printf("%d. %s\n", i + 1, items[i].name); 
    }
}

void edit_db(item_t *items, int max_size) {
    list_db(items, max_size); 
    int change = ask_question_int("Du har valt Redigera en vara, skriv indexet på den varan du vill ändra\n");
    
    while (change > max_size || change < 0) {
        change = ask_question_int("Felaktig input\n");
    }
    change--; 
    
    print_item(&items[change]); 

    printf("Var god skriv in dina ändringar: \n"); 
    item_t updated_item = input_item(); 
    items[change] = updated_item; 

}

item_t add_item_to_db(item_t *items, int new_index) {  
    list_db(items, new_index);  
    printf("Du har valt Lägga till vara, var god skriv in din nya vara: \n"); 
    items[new_index] = input_item();  
    return *items; 
}

int remove_item_from_db(item_t *items, int max_size) {
    list_db(items, max_size); 
    int change = ask_question_int("Du har valt Ta bort en vara, skriv indexet på den varan du vill ta bort\n");
    
    while (change > max_size || change < 0) {
        change = ask_question_int("Felaktig input\n");
    }
    change--; 
    print_item(&items[change]); 

    for (int i = change; i < max_size; i++) {
        items[i] = items[i + 1]; 
    }
    items[max_size - 1] = items[max_size - 2]; 

    return max_size; 
}

void event_loop(item_t *items, int index) {
    bool running = true; 

    do {
        switch (ask_question_menu()) {
            case 'L':
                *items = add_item_to_db(items, index); 
                index++; 
                break;
            case 'T':
                if (index == 0) {
                    printf("Du måste skriva in varor innan du kan ta bort varor\n"); 
                }
                else {
                    index = remove_item_from_db(items, index);
                    index --; 
                }
                break; 
            case 'R':
                if (index == 0) {
                    printf("Du måste skriva in varor innan du kan redigera\n"); 
                }
                else {
                    edit_db(items, index); 
                }
                break;
            case 'G':
                printf("Not yet implemented!\n"); 
                break;
            case 'H': 
                list_db(items, index); 
                break;
            case 'A': 
                running = false; 
                break;
            default:
                break;
        }
        if (index == 16) {
            printf("Du har lagt till max antal varor (16 st), fortsätter du att lägga till varor skrivs det över dina tidigare varor\n"); 
            index = 0; 
        }
    } while (running); 
}

int main() { 
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu
    event_loop(db, db_siz); 
    return 0;
}