#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/hash_table.h"
#include "ui.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

static int cmp_stringp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
    qsort(keys, no_keys, sizeof(char *), cmp_stringp);
}

bool string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.string, e2.string) == 0);
}

unsigned string_sum_hash(elem_t e)
{
    char *str = e.string;
    unsigned result = 0;
    do
    {
        result += *str;
    }
    while (*++str != '\0');
    return result; 
}

static char *merch_exist_check(store_t *store, bool should_exist)
{
    char *input_name = ask_question_string("\nWrite the name of the merch: ");

    while (merch_exists(store, input_name) != should_exist)
    {
        char *new_alt = ask_question_string(
            should_exist
                ? "\nThe merch doesn't exist, do you want to write another one (y/n)? "
                : "\nThe merch already exists, do you want to write another one (y/n)? ");

        if (toupper(*new_alt) == 'Y')
        {
            free(input_name);
            input_name = ask_question_string("\nWrite the name of the merch: ");
        }
        else
        {
            free(new_alt);
            free(input_name);
            return NULL;
        }

        free(new_alt);
    }

    return input_name;
}


static merch_t *input_merch(char *name)
{
    char *description = ask_question_string("\nWrite a description of the merch: "); 
    int price = ask_question_int("\nWrite the price of the merch: ");

    merch_t *new_merch = merch_create(name, description, price, ioopm_linked_list_create(string_eq)); 

    return new_merch; 
}

void add_merch(store_t *store)
{    
    char *input_name = merch_exist_check(store, false);

    if (input_name == NULL)
    {
        free(input_name); 
        return;
    }

    merch_t *input = input_merch(input_name); 

    store_add(store, input); 
}

//TODO: implement when the struct of listed names is complete
void list_merch(store_t *store)
{
    if (store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to list"); 
        return; 
    } 

    //size_t st_size = store_size(store);
    //int fist_print_size = st_size < 20 ? st_size : 20; 

    //char *names[st_size];           //TODO: needs to be allocated?
    //get_names_in_arr(store, names); //TODO: Will be a part of store_t struct??
    //sort_keys(names, st_size); 

    //for (int i; i < fist_print_size; i++)
    //{   
    //    merch_t *merch = get_merch(store, names[i]); 
    //    print_merch(merch); 
    //}
//
    //char *continue_list = ask_question_string("\nPress 'N' to return to menu, press anywhere to continue list ");
    //if (toupper(*continue_list) == 'N' ) 
    //{   
    //    return; 
    //}
    //else 
    //{
    //    for (int i = fist_print_size; i < st_size; i++)
    //    {
    //        merch_t *merch = get_merch(store, names[i]); 
    //        print_merch(merch); 
    //    }
    //}
    //TODO: Wait for response on ed if print only names or traits as well
    //should print 20 at a time
    ioopm_list_t *names = ioopm_hash_table_keys(store);
    size_t names_size = ioopm_linked_list_size(names); 

    for (int i = 0; i < names_size; i++)
    {
        merch_t *merch = ioopm_linked_list_get(names, i).void_ptr; 
        print_merch(merch); 
    }


    ioopm_linked_list_destroy(names); 

    char *continue_list = NULL; 
    int twenty_time = 0; 
    do
    {
        while (twenty_time < 20)
        {
        
            twenty_time++; 
        }
        twenty_time = 0; 
        
        if (twenty_time == 20)
        {
            continue_list = ask_question_string("\nPress 'N' to return to menu, press anywhere to continue list "); 
        }
        free(continue_list); 
    } while (toupper(*continue_list) == 'N'); 

    //free(continue_list); 
    
}

void remove_merch(store_t *store)
{
    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL)
    {
        free(input_name); 
        return;
    }

    char *conf_remove = ask_question_string("\nAre you sure you want to remove this merch? (y/n)"); 

    if (toupper(*conf_remove) == 'Y')
    {
        store_remove(store, input_name); 
    }
    free(conf_remove);

    free(input_name); 
}

void edit_merch(store_t *store)
{
    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 

    char *conf_edit = ask_question_string("\nAre you sure you want to edit this merch? (y/n)"); 

    if (!(toupper(*conf_edit) == 'Y'))
    {
        free(conf_edit); 
        return; 
    }
    free(conf_edit); 
    
    merch_t *merch = get_merch(store, input_name); 
    free(input_name); 

    puts("\nNew name: ");
    char *new_name = merch_exist_check(store, false);

    char *new_description = ask_question_string("\nWrite the new decription: "); 
    set_description(merch, new_description); 
    
    int new_price = ask_question_int("\nWrite the new price: "); 
    set_price(merch, new_price); 

    set_name(store, merch, new_name); 
}

void show_stock(store_t *store)
{
    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 

    merch_t *merch = get_merch(store, input_name); 
    print_stock(merch); 

    free(input_name); 
}

void replenish_stock(store_t *store)
{
    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 

    merch_t *merch = get_merch(store, input_name); 
    free(input_name); 

    printf("\nYou selected this merch:\n"); 
    print_merch(merch); 

    char *input_shelf = ask_question_shelf("\nEnter a shelf to add stock to: "); 
    int input_amount = ask_question_int("\nEnter an amount to increase the stock: "); //TODO: should be fine without freeing??

    while (input_amount < 1)
    {
        input_amount = ask_question_int("\nEnter at least 1: "); 
    }

    location_add(merch, input_shelf, input_amount); 

}

void create_cart(store_t *store)
{



}   

void remove_cart(store_t *store)
{

}

void add_to_cart(store_t *store)
{

}

void remove_from_cart(store_t *store)
{

}

void calculate_cart_cost(store_t *store)
{

}

void checkout_cart(store_t *store)
{

}


void print_menu(void) 
{
    printf("\n[A] Add merchendise\n[L] List merchendise\n[D] Remove merchendise\n[E] Edit merchendise\n"
            "[S] Show stock\n[P] Replenish stock\n[C] Create cart\n[R] Remove cart\n[+] Add to cart\n"
            "[-] Remove item from cart\n[=] Calculate cost of all items in your cart\n[O] Checkout\n[Q] Quit\n"); 

}

void event_loop(store_t *store, int store_size) 
{
    bool running = true; 
    char *quit_confirmation; 

    do 
    {
        print_menu(); 
        char *menu_choice = ask_question_string(" "); 
        switch (toupper(*menu_choice))
        {
            case 'A': 
                add_merch(store); 
                break; 
            case 'L': 
                list_merch(store); 
                 break; 
            case 'D':
                remove_merch(store); 
                break;
            case 'E':
                edit_merch(store); 
                break;
            case 'S': 
                show_stock(store); 
                break;
            case 'P': 
                replenish_stock(store); 
                break;
            case 'C': 
                create_cart(store); 
                break; 
            case 'R':
                remove_cart(store); 
                break; 
            case '+':
                add_to_cart(store); 
                break; 
            case '-': 
                remove_from_cart(store); 
                break; 
            case '=': 
                calculate_cart_cost(store); 
                break; 
            case 'O': 
                checkout_cart(store); 
                break; 
            case 'Q':
                quit_confirmation = ask_question_string("Press 'Y' if you really want to quit");

                if (toupper(*quit_confirmation) == 'Y')
                {
                    running = false; 
                    store_destroy(store); 
                } 
                free(quit_confirmation); 
                break; 
            default:
                menu_choice = ask_question_string("Try again with a valid input\n");
        }
        free(menu_choice); 
    } while (running); 
}

int main() { 
    store_t *store = store_create(string_sum_hash, string_eq); 
    int store_siz = store_size(store); // Antalet varor i arrayen just nu
    event_loop(store, store_siz); 
    return 0;
}