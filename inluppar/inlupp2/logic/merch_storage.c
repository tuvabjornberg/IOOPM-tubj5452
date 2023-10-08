#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "merch_storage.h"

merch_t create_merch(char *name, char *description, int price, char *shelf, int stock)
{
    return; 
}

void store_add(store_t *store, merch_t merch)
{
    return; 
}


void stock_add(merch_t merch, int to_add)
{
    return; 
}

void location_add(merch_t merch, char *shelf)
{
    return; 
}

void store_remove(store_t *store, merch_t merch)
{
    return; 
} 

bool merch_exists(store_t *store, char *name)
{
    return false; 
}

size_t store_size(store_t *store)
{
    return 0; 
}

merch_t get_merch(store_t *store, char *name)
{
    return; 
}

void get_names_in_arr(store_t *store, char *arr_of_names[])
{
    return; 
}

int get_stock(char *name)
{
    return 0; 
}

void set_name(merch_t merch, char *new_name)
{
    return; 
}

void set_description(merch_t merch, char *new_description)
{
    return; 
}

void set_price(merch_t merch, int new_price)
{
    return; 
}

void print_merch(merch_t merch)
{
    return; 
}

void print_stock(merch_t merch)
{
    return; 
}

bool store_is_empty(store_t *store)
{
  return ioopm_hash_table_is_empty(store); 
}

