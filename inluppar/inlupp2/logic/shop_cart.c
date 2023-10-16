#include "shop_cart.h"
#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include <string.h>

carts_t *cart_storage_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    carts_t *new_carts = calloc(1, sizeof(carts_t)); 
    new_carts->carts = ioopm_hash_table_create(hash_fun, eq_fun); 
    new_carts->total_carts = 0; 
}

ioopm_hash_table_t *get_items_in_cart(carts_t *storage_carts, int id)
{
    option_t *lookup_cart = ioopm_hash_table_lookup(storage_carts->carts, int_elem(id)); 
    ioopm_hash_table_t *cart_items = lookup_cart->value.void_ptr; 
    free(lookup_cart); 
    return cart_items; 
}

static void items_in_cart_destroy(elem_t key, elem_t *value, void *arg)
{
    ioopm_hash_table_destroy((ioopm_hash_table_t *) value->void_ptr); 
}

void cart_storage_destroy(carts_t *storage_carts)
{
    ioopm_hash_table_apply_to_all(storage_carts->carts, items_in_cart_destroy, NULL); 
    ioopm_hash_table_destroy(storage_carts->carts); 
    free(storage_carts); 
}

void cart_create(carts_t *storage_carts, ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    ioopm_hash_table_t *new_cart = ioopm_hash_table_create(hash_fun, eq_fun); 
    int id = storage_carts->total_carts; 
    ioopm_hash_table_insert(storage_carts->carts, int_elem(id), void_elem(new_cart)); 
}

void cart_destroy(carts_t *storage_carts, int id)
{
    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, id); 
    
    ioopm_hash_table_destroy(cart_items); 
    ioopm_hash_table_remove(storage_carts->carts, int_elem(id)); 
}

bool carts_is_empty(carts_t *storage_carts)
{
    if (ioopm_hash_table_is_empty(storage_carts->carts)) return true; 
    else return false; 
}


int item_in_cart_amount(carts_t *storage_carts, int id, char *merch_name)
{
    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, id); 
    
    int current_amount = 0; 

    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name));

    if (item_in_cart->success)
    {
        current_amount = item_in_cart->value.integer;
    } 
    free(item_in_cart); 
    
    return current_amount; 
}

//TODO: mem-leak because of strdup
void cart_add(carts_t *storage_carts, int id, char *merch_name, int amount)
{
    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, id); 
    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name)); 

    if (item_in_cart->success)
    {
        int existing_amount = item_in_cart->value.integer; 
        item_in_cart->value.integer = existing_amount + amount; 
    }
    else
    {  
        ioopm_hash_table_insert(cart_items, str_elem(strdup(merch_name)), int_elem(amount)); 
    }
    free(item_in_cart); 
    free(merch_name); 
}


void cart_remove(carts_t *carts, int id, int amount)
{

}


int cost_calculate(carts_t *carts, int id)
{

}


void cart_checkout(carts_t *carts, int id)
{

}