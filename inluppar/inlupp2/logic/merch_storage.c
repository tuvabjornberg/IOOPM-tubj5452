#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "merch_storage.h"

merch_table_t *store_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    return ioopm_hash_table_create(hash_fun, eq_fun); 
}

merch_t *merch_create(char *name, char *description, int price, char *shelf)
{
    merch_t *new_merch = calloc(1, sizeof(merch_t));
    new_merch->name = name;
    new_merch->description = description;
    new_merch->price = price;
    
    new_merch->stock = 0; 

    //ioopm_list_t *locations = ioopm_linked_list_create(); 
    //ioopm_linked_list_append(location_add, shelf); 
    //new_merch->location = 

    return new_merch;
    //return (merch_t *) (NULL); 
}

void store_add(merch_table_t *store, merch_t *merch)
{
    elem_t elem_key = {.string = merch->name};
    elem_t elem_value = {.void_ptr = merch};
    ioopm_hash_table_insert(store, elem_key, elem_value); 
}

void stock_add(merch_t *merch, int to_add)
{
    return; 
}

void location_add(merch_t *merch, char *shelf)
{
    return; 
}


void store_remove(merch_table_t *store, merch_t *merch)
{
    return; 
} 

void location_remove(merch_t *merch, char *shelf)
{
    return; 
}


bool merch_exists(merch_table_t *store, char *name)
{
    return false; 
}

bool shelf_exists(merch_t *merch, char *shelf)
{
    return false; 
}

bool store_is_empty(merch_table_t *store)
{
    return false; 
}


size_t store_size(merch_table_t *store)
{
    return 0; 
}


merch_t *get_merch(merch_table_t *store, char *name)
{ 
    //return ioopm_hash_table_lookup(store, name); 
    return (merch_t *) (NULL); 
}

merch_t get_merch_dummy(merch_table_t *store, char *name)
{
    char *dummy_name = "test_name"; 
    char *dummy_desc = "test_desc"; 
    int dummy_price = 100000; 
    int dummy_stock = -1; 
    ioopm_list_t *dummy_location = NULL; 
    merch_t dummy = {dummy_name, dummy_desc, dummy_price, dummy_stock, dummy_location}; 

    return dummy; 
}

char *get_name(merch_t *merch)
{
    return merch->name; 
}

char *get_description(merch_t *merch)
{
    return merch->description; 
}

int get_price(merch_t *merch)
{
    return merch->price; 
}

void get_names_in_arr(merch_table_t *store, char *arr_of_names[])
{
    return; 
}

int get_stock(char *name)
{
    return 0; 
}

void set_name(merch_t *merch, char *new_name)
{
    return; 
}

void set_description(merch_t *merch, char *new_description)
{
    return; 
}

void set_price(merch_t *merch, int new_price)
{
    return; 
}


void print_merch(merch_t *merch)
{
    return; 
}

void print_stock(merch_t *merch)
{
    return; 
}



void merch_destroy(elem_t name, elem_t *value, void *arg)
{
    free(value->void_ptr); 
}


void store_destroy(merch_table_t *store)
{
    ioopm_hash_table_apply_to_all(store, merch_destroy, NULL); 
    ioopm_hash_table_destroy(store); 
}