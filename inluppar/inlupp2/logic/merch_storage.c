#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"
#include "merch_storage.h"
#include <stdio.h>

store_t *store_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    return ioopm_hash_table_create(hash_fun, eq_fun); 
}

merch_t *merch_create(char *name, char *description, int price, char *shelf)
{
    merch_t *new_merch = calloc(1, sizeof(merch_t));
    new_merch->name = name;
    new_merch->description = description;
    new_merch->price = price;
    
    //ioopm_list_t *locations = ioopm_linked_list_create(); 
    //ioopm_linked_list_append(location_add, shelf); 
    //new_merch->locations = 

    return new_merch;
}


void store_add(store_t *store, merch_t *merch)
{
    ioopm_hash_table_insert(store, str_elem(merch->name), void_elem(merch)); 
}

void stock_add(merch_t *merch, int to_add)
{
    return; 
}
//same?? ^ v
void location_add(merch_t *merch, char *shelf)
{
    //ioopm_linked_list_append(merch->locations, str_elem(shelf)); 
    return; 
}

void store_remove(store_t *store, char *name)
{
    free(get_merch(store, name)); 
    ioopm_hash_table_remove(store, str_elem(name)); 
    return; 
} 

void location_remove(merch_t *merch, char *shelf)
{
    return; 
    //return ioopm_linked_list_remove(merch->locations, INDEX) 
}


bool merch_exists(store_t *store, char *name)
{
    return ioopm_hash_table_has_key(store, str_elem(name)); 
}

bool shelf_exists(merch_t *merch, char *shelf)
{
    return false; 
}


bool store_is_empty(store_t *store)
{
    return ioopm_hash_table_is_empty(store);  
}

size_t store_size(store_t *store)
{
    return ioopm_hash_table_size(store);  
}

size_t locations_size(merch_t *merch)
{
    //return ioopm_linked_list_size(merch->locations); 
    return 0; 
}


merch_t *get_merch(store_t *store, char *name)
{
    option_t *lookup_result = ioopm_hash_table_lookup(store, str_elem(name)); 

    if (lookup_result->success)
    {
        merch_t *merch_found = lookup_result->value.void_ptr; 
        free(lookup_result); 
        return merch_found; 
    }
    else 
    {
        free(lookup_result); 
        return NULL; 
    }
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


void get_names_in_arr(store_t *store, char *arr_of_names[])
{
    //TODO: unfinished!!
    //ioopm_list_t *names = ioopm_hash_table_keys(store); 
    //size_t names_size = ioopm_linked_list_size(names);
//
    //ioopm_list_iterator_t *iter = ioopm_list_iterator(names);
    //elem_t value = ioopm_iterator_current(iter);
//
    //for (int i = 0; i < names_size; i++)
    //{
    //    arr_of_names[i] = value.string;
    //    value = ioopm_iterator_next(iter);
    //}
//
    //sort_keys(keys, ht_size);
    return; 
}

char *get_shelf(store_t *store, char *name, int index)
{
    return NULL; 
}

int get_stock(store_t *store, char *name)
{
    return 0; 
    //return get_merch(store, name)->locations; 
}

//location_t get_location(store_t *store, char *name, char *shelf)
//{
//    //merch_t *merch = get_merch(store, name); 
//    //ioopm_linked_list_get(merch->locations, )
//}

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
    printf("\nName: %s", get_name(merch)); 
    printf("\nDescription: %s", get_description(merch)); 
    printf("\nPrice: %d", get_price(merch)); 
    //printf("\nLocations: %ld", get_locations(merch)); 
    return; 
}

void print_stock(merch_t *merch)
{
    //printf("\nLocations: %ld", get_locations(merch)); 
    return; 
}



void merch_destroy(elem_t name, elem_t *value, void *arg)
{
    free(value->void_ptr); 
}


void store_destroy(store_t *store)
{
    ioopm_hash_table_apply_to_all(store, merch_destroy, NULL); 
    ioopm_hash_table_destroy(store); 
}
