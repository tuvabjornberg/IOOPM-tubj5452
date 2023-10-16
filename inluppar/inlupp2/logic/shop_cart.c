#include "shop_cart.h"
#include <string.h>
#include <stdbool.h>

carts_t *cart_storage_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    carts_t *new_carts = calloc(1, sizeof(carts_t)); 
    new_carts->carts = ioopm_hash_table_create(hash_fun, eq_fun); 
    new_carts->total_carts = 0;
    return new_carts;
}

ioopm_hash_table_t *get_items_in_cart(carts_t *storage_carts, int id)
{
    option_t *lookup_cart = ioopm_hash_table_lookup(storage_carts->carts, int_elem(id)); 
    ioopm_hash_table_t *cart_items = lookup_cart->value.void_ptr; 
    free(lookup_cart); 
    return cart_items; 
}

bool has_merch_in_cart(ioopm_hash_table_t *cart_items, char *name)
{
    return ioopm_hash_table_has_key(cart_items, str_elem(name));
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

//TODO: förmodligen implementerad fel mot beskrivningen
void cart_add(carts_t *storage_carts, int id, char *merch_name, int quantity)
{
    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, id); 
    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name)); 

    if (item_in_cart->success)
    {
        int existing_quantity = item_in_cart->value.integer; 
        item_in_cart->value.integer = existing_quantity + quantity; 
    }
    else
    {  
        ioopm_hash_table_insert(cart_items, str_elem(merch_name), int_elem(quantity)); 
    }
    free(item_in_cart); 
}


void cart_remove(ioopm_hash_table_t *cart_items, char *merch_name, int amount)
{
    option_t *item_in_cart = ioopm_hash_table_lookup(cart_items, str_elem(merch_name));
    
    if (item_in_cart->success)
    {
        int existing_amount = item_in_cart->value.integer;
        if (existing_amount > amount)
        {
            existing_amount -= amount;
            ioopm_hash_table_insert(cart_items, str_elem(merch_name), int_elem(existing_amount));
        }
        else
        {
            ioopm_hash_table_remove(cart_items, str_elem(merch_name));
        }
    }
    free(item_in_cart); 

}

int cost_calculate(store_t *store, carts_t *storage_carts, int id)
{
    int total_cost = 0;
    ioopm_hash_table_t *cart_items = get_items_in_cart(storage_carts, id);

    ioopm_list_t *keys = ioopm_hash_table_keys(cart_items);
    for (int i = 0; i < ioopm_linked_list_size(keys); ++i)
    {
        elem_t key = ioopm_linked_list_get(keys, i);
        option_t *value = ioopm_hash_table_lookup(cart_items, key);
        if (value->success)
        {
	  total_cost += value->value.integer * get_price(get_merch(store, key.string));
        }
        free(value);
    }
    ioopm_linked_list_destroy(keys);
    return total_cost;
}


void cart_checkout(carts_t *storage_carts, int id)
{

}
