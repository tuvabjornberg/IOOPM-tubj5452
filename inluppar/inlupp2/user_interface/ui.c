#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"
#include "merch_storage.h"
#include "linked_list.h"
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

/*
typedef bool(fun)(merch_table_t *store, char *name);
static char *valid_merch(merch_table_t *store, char *name, fun exist_fun) //TODO: abstarction
{
    while (!fun(store, name))
    {
        char *new_alt = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            name = ask_question_string("\nWrite the name of the merch: "); 
        }
        else
        {
            return; 
        }
    }
    return name; 

}
*/

merch_t input_merch(void)
{
    char *name = ask_question_string("\nWrite the name of the merch: "); 
    char *description = ask_question_string("\nWrite a description of the merch: "); 
    int price = ask_question_int("\nWrite the price of the merch: ");
    char *shelf = ask_question_shelf("\nWrite the shelf (Format: 'A36')"); 
    int stock = get_stock_of_merch(*name); 
    return create_merch(name, description, price, shelf, stock); 
}

void add_merch(merch_table_t *store)
{    
    merch_t input = input_merch(); 

    while (merch_exists(store, input.name))
    {
        char *new_alt = ask_question_string("\nThe merch already exists, do you want to add another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            input = input_merch();  
        }
        else 
        {
            return; 
        }
    }

    store_add(store, input); 

}

void list_merch(merch_table_t *store)
{
    if (store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to list"); 
        return; 
    } 

    size_t st_size = store_size(store);
    int fist_print_size = st_size < 20 ? st_size : 20; 

    char *names[st_size]; 
    get_names_in_arr(store, names); 
    sort_keys(names, st_size); 

    for (int i; i < fist_print_size; i++)
    {   
        merch_t merch = get_merch(store, names[i]); 
        print_merch(get_merch(store, names[i])); 
    }

    char *continue_list = ask_qustion_string("\nPress 'N' to return to menu, press anywhere to continue list ");
    if (toupper(*continue_list) == 'N' ) 
    {   
        return; 
    }
    else 
    {
        for (int i = fist_print_size; i < st_size; i++)
        {
            merch_t merch = get_merch(store, names[i]); 
            print_merch(merch); 
        }
    }

}

void remove_merch(merch_table_t *store)
{
    char *input_name = ask_question_string("\nWrite the name of the merch you want to remove: "); 

    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    while (!merch_exists(store, input_name))
    {
        char *new_alt = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            input_name = ask_question_string("\nWrite the name of the merch you want to remove: "); 
        }
        else
        {
            return; 
        }
    }

    char *conf_remove = ask_qustion_string("\nAre you sure you want to remove this merch? \n"); 

    if (toupper(*conf_remove) == 'Y')
    {
        merch_t merch = get_merch(store, input_name); 
        store_remove(store, merch); 
    }
    return; 
}

void edit_merch(merch_table_t *store)
{
    char *input_name = ask_question_string("\nWrite the name of the merch you want to edit: "); 

    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    while (!merch_exists(store, input_name))
    {
        char *new_alt = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            input_name = ask_question_string("\nWrite the name of the merch you want to edit: "); 
        }
        else
        {
            return; 
        }
    }

    char *conf_edit = ask_qustion_string("\nAre you sure you want to edit this merch? "); 

    if (!toupper(*conf_edit) == 'Y')
    {
        return; 
    }
    
    merch_t merch = get_merch(store, input_name); 
    char *alt_edit = ask_question_string("\nChoose what you want to edit:\n[A] Edit name\n[B] Edit description\n[C] Edit price\n"); 

    //TODO: does not handle not affect stock, if name is changed the key is also changed
    //make adjustments!!
    switch (toupper(*alt_edit)) 
    {
        case 'A':
            char *new_name = ask_question_string("\nWrite the new name: "); 
            set_name(merch, *new_name); 
            break; 
        case 'B': 
            char *new_description = ask_question_string("\nWrite the new decription: "); 
            set_description(merch, *new_description); 
            break; 
        case 'C': 
            char *new_price = ask_question_string("\nWrite the new price: "); 
            set_price(merch, *new_price); 
            break; 
        default:
            alt_edit = ask_question_string("Try again with a valid input \n");
    } 

}

void show_stock(merch_table_t *store)
{
    char *input_name = ask_question_string("\nWrite the name of the merch whose stock you want listed: "); 

    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    while (!merch_exists(store, input_name))
    {
        char *new_alt = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            input_name = ask_question_string("\nWrite the name of the merch whose stock you want listed: "); 
        }
        else
        {
            return; 
        }
    }

    merch_t merch = get_merch(store, input_name); 

    print_stock(merch); 

}

void replenish_stock(merch_table_t *store)
{
    char *input_name = ask_question_string("\nWrite the name of the merch whose stock you want replenished: "); 

    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    while (!merch_exists(store, input_name))
    {
        char *new_alt = ask_question_string("\nThe merch doesn't exist, do you want t write another one (y)? "); 
        if (toupper(new_alt) == 'Y')
        {
            input_name = ask_question_string("\nWrite the name of the merch whose stock you want replenished: "); 
        }
        else
        {
            return; 
        }
    }

    merch_t merch = get_merch(store, input_name); 

    printf("\nYou selected this merch:\n"); 
    print_merch(merch); 

    char *input_shelf = ask_question_shelf("\nEnter the storage location you want to replenish: "); 

    //while (!shelf_exists(store, input_name, input_shelf))
    //{
    //    char *new_alt = ask_question_string("\nThe shelf doesn't exist, do you want t write another one (y)? "); 
    //    if (toupper(new_alt) == 'Y')
    //    {
    //        input_name = ask_question_string("\nWrite the name of the merch whose stock you want replenished: "); 
    //    }
    //    else
    //    {
    //        return; 
    //    }
    //}



/*

    Increases the stock of a merch by at least one.
    You can replenish on an existing storage location or a new one.
    The stock for a merch is the sum of all items on all storage locations holding that merch.
    A storage location stocks items of one (type of) merch, never more.
    For simplicity, there is no limit to the amount of storage locations nor is there a limit on the number of items a location can hold.
    The action code should be "P". The action should read the id of the storage location, the name of the merch and the number of items to add.

*/

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