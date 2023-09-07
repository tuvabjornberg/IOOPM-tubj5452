#ifndef __DB_H__
#define __DB_H__

#include <stdbool.h>

typedef struct item {
    char *name; 
    char *description; 
    int price; 
    char *shelf; 
} item_t;

void print_item(item_t *item); 
item_t make_item(char *name, char *description, int price, char *shelf); 
item_t input_item(void); 
char *magick(char **array1, char **array2, char **array3, int size); 
void print_menu(void); 
char ask_question_menu(void); 
void list_db(item_t *items, int no_items); 
void edit_db(item_t *items, int max_size); 
item_t add_item_to_db(item_t *items, int new_index); 
int remove_item_from_db(item_t *items, int max_size); 
void event_loop(item_t *items, int index); 

#endif
