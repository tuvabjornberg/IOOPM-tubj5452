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

static char *exist_check(merch_table_t *store, char *prompt)
{
    if (store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to %s", prompt); 
        return; 
    }

    char *user_input = ask_question_string("\nWrite the name of the merch: "); 

    while (!merch_exists(store, user_input))
    {
        char *choice = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(choice) == 'Y')
        {
            user_input = ask_question_string("\nWrite the name of the merch: "); 
        }
    }
    return user_input; 
}

merch_t input_merch(void)
{
    char *name = ask_question_string("\nWrite the name of the merch: "); 
    char *description = ask_question_string("\nWrite a description of the merch: "); 
    int price = ask_question_int("\nWrite the price of the merch: ");
    int stock = get_stock_of_merch(*name); 
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
    char *user_input_to_remove = exist_check(store, "remove"); 

    char *remove_confirmation = ask_qustion_string("\nAre you sure you want to remove:\n"); 
    print_merch(user_input_to_remove); 

    if (toupper(*remove_confirmation) == 'Y')
    {
        merch_t merch_to_remove = get_merch_from_store(store, user_input_to_remove); 
        remove_merch_from_store(store, merch_to_remove); 
    }

}

void edit_merch(merch_table_t *store)
{
    char *user_input_to_edit = exist_check(store, "edit"); 

    char *edit_confirmation = ask_qustion_string("\nAre you sure you want to edit:\n"); 
    print_merch(user_input_to_edit); 

    if (!toupper(*edit_confirmation) == 'Y')
    {
        return; 
    }
    
    merch_t merch_to_edit = get_merch_from_store(store, user_input_to_edit); 
    char *user_edit_input = ask_question_string("\nChoose what you want to edit:\n[A] Edit name\n[B] Edit description\n[C] Edit price\n"); 

    //TODO: does not handle not affect stock, if name is changed the key is also changed
    //make adjustments!!
    switch (toupper(*user_edit_input)) 
    {
        case 'A':
            char *new_name = ask_question_string("\nWrite the new name: "); 
            set_name(merch_to_edit, *new_name); 
            break; 
        case 'B': 
            char *new_description = ask_question_string("\nWrite the new decription: "); 
            set_description(merch_to_edit, *new_description); 
            break; 
        case 'C': 
            char *new_price = ask_question_string("\nWrite the new price: "); 
            set_price(merch_to_edit, *new_price); 
            break; 
        default:
            user_edit_input = ask_question_string("Try again with a valid input\n");
    } 

}

void show_stock(merch_table_t *store)
{

    /*
    List all the storage locations for a particular merch, along with the quantities stored on each location. 
    Storage locations should preferably be listed in alphabetical order (e.g., A20 before B01 and C01 before C10).
    Names of storage locations follow this format always: one capital letter (A-Z) followed by two digits (0-9).
    The action code should be "S. The action should read the name of the merch.

*/

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
    merch_table_t *store = ioopm_hash_table_create(hash_fun, cmp_stringp); 
    int store_siz = get_store_size(store); // Antalet varor i arrayen just nu
    event_loop(store, store_siz); 
    return 0;
}