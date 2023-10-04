#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"
#include "merch_storage.h"
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

merch_t input_merch(void)
{
    char *name = ask_question_string("\nWrite the name of the merch: "); 
    char *description = ask_question_string("\nWrite a description of the merch: "); 
    int price = ask_question_int("\nWrite the price of the merch: ");
    return create_item(name, description, price, stock); 
}

void add_merch(merch_table_t *store)
{    
    merch_t input = input_merch(); 

    while (merch_exists(store, input.name))
    {
        char *choice = ask_question_string("\nThe merch already exists, do you want to add another one (y)? "); 
        if (toupper(choice) == 'Y')
        {
            input = input_merch();  
        }
        else 
        {
            return; 
        }
    }

    add_merch_to_store(store, input); 

}

void list_merch(merch_table_t *store)
{
    if (store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to list"); 
        return; 
    } 

    int store_size = get_store_size(store);
    int fist_print_size = store_size < 20 ? store_size : 20; 

    int current = 0; 

    char *arr_of_names[store_size]; 
    get_merch_in_arr(store, arr_of_names); 
    sort_keys(arr_of_names, store_size); 

    for (int i; i < fist_print_size; i++)
    {   
        print_merch(arr_of_names[i]); 
    }

    char *continue_list = ask_qustion_string("\nPress 'N' to return to menu, press anywhere to continue list ");
    if (toupper(*continue_list) == 'N' ) 
    {   
        return; 
    }
    else 
    {
        for (int i = fist_print_size; i < store_size; i++)
        {
            print_merch(arr_of_names[i]); 
        }
    }

}

void remove_merch(merch_table_t *store)
{
    if (store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to remove"); 
        return; 
    } 

    char *name_to_remove = ask_question_string("\nWrite the name of the merch to remove: "); 

    while (!merch_exists(store, name_to_remove))
    {
        char *choice = ask_question_string("\nThe merch doesn't exist, do you want to remove another one (y)? "); 
        if (toupper(choice) == 'Y')
        {
            name_to_remove = ask_question_string("\nWrite the name of the merch to remove: "); 
        }
    }

    char *remove_confirmation = ask_qustion_string("\nAre you sure you want to remove:\n"); 
    print_merch(name_to_remove); 

    if (toupper(*remove_confirmation) == 'Y')
    {
        merch_t merch_to_remove = get_merch_from_store(store, name_to_remove); 
        remove_merch_from_store(store, merch_to_remove); 
    }

}

void edit_merch(merch_table_t *store)
{

}

void show_stock(merch_table_t *store)
{

}

void replenish_stock(merch_table_t *store)
{

}

void create_cart(merch_table_t *store)
{

}   

void remove_cart(merch_table_t *store)
{

}

void add_to_cart(merch_table_t *store)
{

}

void remove_from_cart(merch_table_t *store)
{

}

void calculate_cart_cost(merch_table_t *store)
{

}

void checkout_cart(merch_table_t *store)
{

}

//FIXME: OBS! print_menu, ask_question_menu, main from store.c (lab 5), with modifications

void print_menu(void) 
{
    printf("\n[A] Add merchendise\n[L] List merchendise\n[D] Remove merchendise\n[E] Edit merchendise\n"
            "[S] Show stock\n[P] Replenish stock\n[C] Create cart\n[R] Remove cart\n[+] Add to cart\n"
            "[-] Remove item from cart\n[=] Calculate cost of all items in your cart\n[O] Checkout\n[Q] Quit\n"); 

}

char ask_question_menu(void) 
{
    print_menu(); 
    char *user_input = ask_question_string("");
    int valid_user_input = 0; 

    do 
    {
        switch (toupper(*user_input)) 
        {
            case 'A':
            case 'L': 
            case 'D': 
            case 'E': 
            case 'S': 
            case 'P': 
            case 'C': 
            case 'R': 
            case '+': //should work with toupper?
            case '-': //-||-
            case '=': //-||-
            case 'O': 
            case 'Q': 
                valid_user_input = 1; 
                break;
            default:
                user_input = ask_question_string("Try again with a valid input\n");
            } 
    }
    while(!valid_user_input); 

    return toupper(*user_input);
}


void event_loop(merch_table_t *store, int store_size) 
{
    bool running = true; 

    do 
    {
        switch (ask_question_menu()) 
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
                char *quit_confirmation = ask_qustion_string("Press 'Y' if you really want to quit");

                if (toupper(*quit_confirmation) == 'Y')
                {
                    running = false; 
                } 
                break;
            default:
                break;
        }
        //error handling??
        //if (store_size == 16) {
        //    printf("Du har lagt till max antal varor (16 st), fortsätter du att lägga till varor skrivs det över dina tidigare varor\n"); 
        //    store_size = 0; 
        //}
    } while (running); 
}

int main() { 
    merch_table_t *store = ioopm_hash_table_create(hash_fun, eq_fun); 
    int store_siz = 0; // Antalet varor i arrayen just nu
    event_loop(store, store_siz); 
    return 0;
}