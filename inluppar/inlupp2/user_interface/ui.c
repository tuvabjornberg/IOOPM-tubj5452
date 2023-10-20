#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "../utils/hash_fun.h"
#include "ui.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

static char *merch_exist_check(store_t *store, bool should_exist)
{
    char *input_name = ioopm_ask_question_string("\nWrite the name of the merch: ");

    while (ioopm_merch_exist(store, input_name) != should_exist)
    {
        char *new_alt = ioopm_ask_question_string(
            should_exist
                ? "\nThe merch doesn't exist, do you want to write another one (y/n)? "
                : "\nThe merch already exists, do you want to write another one (y/n)? ");

        if (toupper(*new_alt) == 'Y')
        {
            free(input_name);
            input_name = ioopm_ask_question_string("\nWrite the name of the merch: ");
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

static int merch_quantity_check(store_t *store, char *merch_name, int current_amount)
{
    merch_t *merch = ioopm_merch_get(store, merch_name); 
    if (current_amount == merch->stock_size) 
    {
        puts("There are no more items in stock to add to cart"); 
        return -1; 
    }

    printf("Amount in stock: %d", merch->stock_size); 
    int input_amount = ioopm_ask_question_int("\nEnter the amount of the merch to add to cart: "); 

    while (input_amount > merch->stock_size - current_amount)
    {
        char *new_alt = ioopm_ask_question_string("\nThe store doesn't carry that many items, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_amount = ioopm_ask_question_int("\nWrite the amount to add to cart: "); 
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

//TODO: better place for -1 for input_id???
static int cart_exists_check(carts_t *storage_carts)
{
    int input_id = ioopm_ask_question_int("\nWrite the ID of the cart: ") - 1; 

    while (!ioopm_hash_table_has_key(storage_carts->carts, int_elem(input_id)))
    {
        char *new_alt = ioopm_ask_question_string("\nThe cart doesn't exist, do you want to write another one (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_id = ioopm_ask_question_int("\nWrite the ID of the cart: ") - 1; 
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

static char *merch_in_cart_check(ioopm_hash_table_t *cart_items)
{
    char *input_name = ioopm_ask_question_string("\nWrite the merch to remove items from: ");     
    while (!ioopm_has_merch_in_cart(cart_items, input_name)) 
    {
       char *new_alt = ioopm_ask_question_string("\nYour cart doesn't have that merch, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_name = ioopm_ask_question_string("\nWrite the merch to remove items from: "); 
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

static int cart_quantity_check(carts_t *storage_carts, int input_id, char *input_name)
{
    int input_quantity = ioopm_ask_question_int("\nEnter the quantity of items to remove: ");

    int merch_cart_amount = ioopm_item_in_cart_amount(storage_carts, input_id, input_name); 

    while (input_quantity > merch_cart_amount || input_quantity < 0)
    {
       char *new_alt = ioopm_ask_question_string("\nYour cart doesn't have that quantity, do you want another try (y/n)? "); 

        if (toupper(*new_alt) == 'Y')
        {
            input_quantity = ioopm_ask_question_int("\nWrite the amount to remove from cart: "); 
        }
        else
        {
            free(new_alt);
            free(input_name); 
            return -1;
        }
        free(new_alt);  
    }
    return input_quantity; 
}

static merch_t *merch_input(char *name)
{
    char *description = ioopm_ask_question_string("\nWrite a description of the merch: "); 
    int price = ioopm_ask_question_int("\nWrite the price of the merch: ");
    int stock_size = 0; 

    merch_t *new_merch = ioopm_merch_create(name, description, price, ioopm_linked_list_create(ioopm_string_eq), stock_size); 

    return new_merch; 
}

void merch_add(store_t *store)
{    
    char *input_name = merch_exist_check(store, false);
    if (input_name == NULL) return;

    merch_t *input = merch_input(input_name); 

    ioopm_store_add(store, input); 
}

void merch_list(store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        printf("\nThe store is empty, no merch to list"); 
        return; 
    }

    int i = 0;
    for (; i < store->merch_count && i < PRINT_AT_A_TIME; i++)
    {
      puts(store->merch_names[i]);
    }

    if (store->merch_count > PRINT_AT_A_TIME)
    {
        char *descision = ioopm_ask_question_string("Press any key to see more items, N/n to return");
	    while (toupper(descision[0]) != 'N' && i < store->merch_count)
        {
	      for (; i < store->merch_count && i < store->merch_count + PRINT_AT_A_TIME; i++)
          {
		    puts(store->merch_names[i]);
	      }

	      free(descision);
	      descision = ioopm_ask_question_string("Press any key to see more items, N/n to return");
	    }

	    free(descision);
    }    
}

void merch_remove(store_t *store, carts_t *storage_carts)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return;

    char *conf_remove = ioopm_ask_question_string("\nAre you sure you want to remove this merch? (y/n)"); 
    if (toupper(*conf_remove) == 'Y')
    {
        ioopm_store_remove(store, storage_carts->carts, input_name); 
    }

    free(conf_remove);
    free(input_name); 
}

void merch_edit(store_t *store, carts_t *storage_carts)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 
    
    merch_t *merch = ioopm_merch_get(store, input_name); 

    puts("\nNew name: ");
    char *new_name = merch_exist_check(store, false);
    char *new_description = ioopm_ask_question_string("\nWrite the new decription: "); 
    int new_price = ioopm_ask_question_int("\nWrite the new price: "); 

    char *conf_edit = ioopm_ask_question_string("\nAre you sure you want to edit this merch? (y/n)"); 
    if (!(toupper(*conf_edit) == 'Y'))
    { 
        free(conf_edit);	
	    free(new_name);
        free(new_description); 
        return; 
    }
    free(conf_edit); 

    ioopm_description_set(merch, new_description); 
    ioopm_price_set(merch, new_price); 
    ioopm_name_set(store, merch, new_name, storage_carts->carts); 

    printf("\nYou have edited: %s", input_name); 
    
    free(input_name); 
}

void stock_list(store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 

    merch_t *merch = ioopm_merch_get(store, input_name); 

    ioopm_stock_print(merch); 

    free(input_name); 
}

void stock_replenish(store_t *store)
{
    if (ioopm_store_is_empty(store)) 
    {
        puts("\nThe store is empty, please add items first"); 
        return; 
    }

    char *input_name = merch_exist_check(store, true);
    if (input_name == NULL) return; 

    merch_t *merch = ioopm_merch_get(store, input_name); 
    free(input_name); 

    printf("\nYou selected this merch:\n"); 
    ioopm_merch_print(merch); 

    char *input_shelf = ioopm_ask_question_shelf("\nEnter a shelf to add stock to: ");

    //TODO: Not duplicate shelf, not more than one merch on each shelf
    //Idea: add an element to the store-struct of an ht(?)/list(?) of each shelf in use. 
    //char *input_shelf = shelf_exist_check(store); 

    int input_amount = ioopm_ask_question_int("\nEnter an amount to increase the stock: "); 
    while (input_amount < 1)
    {
        input_amount = ioopm_ask_question_int("\nEnter at least 1: "); 
    }

    ioopm_location_add(merch, input_shelf, input_amount); 
}

void cart_create(carts_t *storage_carts)
{
    ioopm_cart_create(storage_carts); 
    storage_carts->total_carts++; 

    printf("\nYou have created a cart with the ID: %d", storage_carts->total_carts); 
}   

void cart_destroy(store_t *store, carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *conf_remove = ioopm_ask_question_string("\nAre you sure you want to remove this cart? (y/n)"); 
    if (!(toupper(*conf_remove) == 'Y'))
    {
        free(conf_remove);  
        return; 
    }
    free(conf_remove);

    printf("You have removed this cart: %d", input_id + 1);
    ioopm_cart_destroy(storage_carts, input_id); 
}

//TODO: förmodligen implementerad fel mot beskrivningen
void cart_add(store_t *store, carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    char *input_name = merch_exist_check(store, true); 
    if (input_name == NULL) return; 

    int merch_cart_amount = ioopm_item_in_cart_amount(storage_carts, input_id, input_name); 
    int input_quantity = merch_quantity_check(store, input_name, merch_cart_amount); 
    if (input_quantity == -1) return; 

    merch_t *merch = ioopm_merch_get(store, input_name);
    merch->reserved_stock += input_quantity; 

    ioopm_cart_add(storage_carts, input_id, merch->name, input_quantity); 

    printf("You have added %d of %s to this cart: %d", input_quantity, input_name, input_id + 1); 
    free(input_name); 
}

void cart_remove(store_t *store, carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts)) 
    {
        puts("\nThere are no carts, please add one first"); 
        return; 
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return; 

    ioopm_hash_table_t *cart_items = ioopm_items_in_cart_get(storage_carts, input_id); 

    char *input_name = merch_in_cart_check(cart_items); 
    if (input_name == NULL) return;

    int input_quantity = cart_quantity_check(storage_carts, input_id, input_name); 
    if (input_quantity == -1) return; 

    merch_t *merch = ioopm_merch_get(store, input_name);
    merch->reserved_stock -= input_quantity;

    ioopm_cart_remove(cart_items, input_name, input_quantity); 
    printf("Removed %d %s from cart %d.\n", input_quantity, input_name, input_id + 1);
    free(input_name); 
}

void cart_cost_calculate(store_t *store, carts_t *storage_carts)
{
    if (ioopm_carts_are_empty(storage_carts))
    {
        puts("\nThere are no carts, please add one first");
        return;
    }

    int input_id = cart_exists_check(storage_carts);
    if (input_id == -1) return;

    int total_cost = ioopm_cost_calculate(store, storage_carts, input_id);
    printf("The total cost of cart %d is %d SEK.\n", input_id + 1, total_cost);
}

void cart_checkout(store_t *store)
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
        char *menu_choice = ioopm_ask_question_string(" "); 
        switch (toupper(*menu_choice))
        {
            case 'A': 
                merch_add(store); 
                break; 
            case 'L': 
                merch_list(store); 
                break; 
            case 'D':
                merch_remove(store, storage_carts); 
                break;
            case 'E':
                merch_edit(store, storage_carts); 
                break;
            case 'S': 
                stock_list(store); 
                break;
            case 'P': 
                stock_replenish(store); 
                break;
            case 'C': 
                cart_create(storage_carts); 
                break; 
            case 'R':
                cart_destroy(store, storage_carts); 
                break; 
            case '+':
                cart_add(store, storage_carts); 
                break; 
            case '-': 
	            cart_remove(store, storage_carts); 
                break; 
            case '=': 
	            cart_cost_calculate(store, storage_carts); 
                break; 
            case 'O': 
                cart_checkout(store); 
                break; 
            case 'Q':
                quit_confirmation = ioopm_ask_question_string("Press 'Y' if you really want to quit");

                if (toupper(*quit_confirmation) == 'Y')
                {
                    running = false; 
                    ioopm_cart_storage_destroy(storage_carts);  
                    ioopm_store_destroy(store);
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
    store_t *store = ioopm_store_create(); 
    carts_t *storage_carts = ioopm_cart_storage_create(); 
    event_loop(store, storage_carts); 
    return 0;
}
