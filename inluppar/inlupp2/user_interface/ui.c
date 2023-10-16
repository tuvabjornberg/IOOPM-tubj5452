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

bool string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.string, e2.string) == 0);
}

bool int_eq(elem_t e1, elem_t e2)
{
    return (e1.integer == e2.integer);
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

static unsigned hash_fun_key_int(elem_t key)
{
  return key.integer;
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
    int stock_size = 0; 

    merch_t *new_merch = merch_create(name, description, price, ioopm_linked_list_create(string_eq), stock_size); 

    return new_merch; 
}

void add_merch(store_t *store)
{    
    char *input_name = merch_exist_check(store, false);

    if (input_name == NULL) return;

    merch_t *input = input_merch(input_name); 

    store_add(store, input); 
}

//TODO: implement when the struct of listed names is complete
void list_merch(store_t *store)
{

}

void remove_merch(store_t *store)
{
    if (store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return;

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
    
    merch_t *merch = get_merch(store, input_name); 
    free(input_name); 

    puts("\nNew name: ");
    char *new_name = merch_exist_check(store, false);

    char *new_description = ask_question_string("\nWrite the new decription: "); 
    set_description(merch, new_description); 
    
    int new_price = ask_question_int("\nWrite the new price: "); 
    set_price(merch, new_price); 

    char *conf_edit = ask_question_string("\nAre you sure you want to edit this merch? (y/n)"); 

    if (!(toupper(*conf_edit) == 'Y'))
    {
        free(conf_edit); 
        return; 
    }
    free(conf_edit); 

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
/*
//TODO: part of 
static char *shelf_exist_check(store_t *store)
{
    char *input_shelf = ask_question_shelf("\nEnter a shelf to add stock to: ");

    while (shelf_exists(store, shelf))
    {
        char *new_alt = ask_question_string("\nThe shelf already exists, do you want to write another one (y/n)? ");

        if (toupper(*new_alt) == 'Y')
        {
            free(input_shelf);
            input_shelf = ask_question_string("\nWrite the name of the shelf: ");
        }
        else
        {
            free(new_alt);
            free(input_shelf);
            return NULL;
        }

        free(new_alt);
    }

    return input_shelf;
}
*/
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

    //TODO: Not duplicate shelf, not more than one merch on each shelf
    //Idea: add an element to the store-struct of an ht(?)/list(?) of each shelf in use. 
    //char *input_shelf = shelf_exist_check(store); 

    int input_amount = ask_question_int("\nEnter an amount to increase the stock: "); 

    while (input_amount < 1)
    {
        input_amount = ask_question_int("\nEnter at least 1: "); 
    }

    location_add(merch, input_shelf, input_amount); 

}

void cart_create_ui(carts_t *storage_carts)
{
    cart_create(storage_carts, string_sum_hash, string_eq); 
    storage_carts->total_carts++; 
    printf("\nYou have created a cart with the ID: %d", storage_carts->total_carts); 
}   

//TODO: better place for -1 for input_id???
static int cart_exists_check(carts_t *storage_carts)
{
    int input_id = ask_question_int("\nWrite the ID of the cart: ") - 1; 

    while (!ioopm_hash_table_has_key(storage_carts->carts, int_elem(input_id)))
    {
        char *new_alt = ask_question_string("\nThe cart doesn't exist, do you want to write another one (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_id = ask_question_int("\nWrite the ID of the cart: ") - 1; 
        }
        else
        {
            free(new_alt);
            return -1;
        }
        free(new_alt); 
    }
    return input_id; 
}

void remove_cart(store_t *store, carts_t *storage_carts)
{
    if (carts_is_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *conf_remove = ask_question_string("\nAre you sure you want to remove this cart? (y/n)"); 

    if (!(toupper(*conf_remove) == 'Y'))
    {
        free(conf_remove);  
        return; 
    }
    free(conf_remove);

    cart_destroy(storage_carts, input_id); 
    printf("You have removed this cart: %d", input_id + 1);
}

static int quantity_check(store_t *store, char *merch_name, int current_amount)
{
    merch_t *merch = get_merch(store, merch_name); 
    if (current_amount == merch->stock_size) 
    {
        puts("There are no more items in stock to add to cart"); 
        return -1; 
    }

    printf("Amount in stock: %d", merch->stock_size); 
    int input_amount = ask_question_int("\nEnter the amount of the merch to add to cart: "); 

    while (input_amount > merch->stock_size - current_amount)
    {
        char *new_alt = ask_question_string("\nThe store doesn't carry that many items, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_amount = ask_question_int("\nWrite the amount to add to cart: "); 
        }
        else
        {
            free(new_alt);
            return -1;
        }
        free(new_alt); 
    }
    
    return input_amount; 
}

//TODO: förmodligen implementerad fel mot beskrivningen
void add_to_cart(store_t *store, carts_t *storage_carts)
{
    if (carts_is_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *input_name = merch_exist_check(store, true); 
    if (input_name == NULL) return; 

    int merch_cart_amount = item_in_cart_amount(storage_carts, input_id, input_name); 
    int input_quantity = quantity_check(store, input_name, merch_cart_amount); 
    if (input_quantity == -1) return; 

    cart_add(storage_carts, input_id, input_name, input_quantity); 
    printf("You have added %d of %s to this cart: %d", input_quantity, input_name, input_id + 1); 
    free(input_name); 
}

void remove_from_cart(store_t *store, carts_t *storage_carts)
{
    if (carts_is_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, input_id); 
    char *input_name = ask_question_string("\nWrite the merch to remove items from: ");     
    while (!has_merch_in_cart(cart_items, input_name))
    {
       char *new_alt = ask_question_string("\nYour cart doesn't have that merch, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_name = ask_question_string("\nWrite the merch to remove items from: "); 
        }
        else
        {
            free(new_alt);
            free(input_name); 
            return; 
        }
        free(new_alt);  
    }

    int input_quantity = ask_question_int("\nEnter the quantity of items to remove: "); 
    int merch_cart_amount = item_in_cart_amount(storage_carts, input_id, input_name); 
    while (input_quantity > merch_cart_amount || input_quantity < 0)
    {
       char *new_alt = ask_question_string("\nYour cart doesn't have that quantity, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_quantity = ask_question_int("\nWrite the amount to remove from cart: "); 
        }
        else
        {
            free(new_alt);
            free(input_name); 
            return;
        }
        free(new_alt);  
    }

    cart_remove(cart_items, input_name, input_quantity); 
    free(input_name); 
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

void event_loop(store_t *store, carts_t *storage_carts) 
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
                cart_create_ui(storage_carts); 
                break; 
            case 'R':
                remove_cart(store, storage_carts); 
                break; 
            case '+':
                add_to_cart(store, storage_carts); 
                break; 
            case '-': 
                remove_from_cart(store, storage_carts); 
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
                    cart_storage_destroy(storage_carts);  
                    store_destroy(store);
                } 
                free(quit_confirmation); 
                break; 
            default:
                puts("\nTry again with a valid input"); 
        }
        free(menu_choice); 
    } while (running); 
}

int main() { 
    store_t *store = store_create(string_sum_hash, string_eq); 
    carts_t *storage_carts = cart_storage_create(hash_fun_key_int, int_eq); 
    event_loop(store, storage_carts); 
    return 0;
}