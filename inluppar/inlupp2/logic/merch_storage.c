#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"
#include "merch_storage.h"
#include <stdio.h>
#include <string.h>

store_t *store_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
    return ioopm_hash_table_create(hash_fun, eq_fun); 
}

merch_t *merch_create(char *name, char *description, int price, ioopm_list_t *stock)
{
    merch_t *new_merch = calloc(1, sizeof(merch_t));
    new_merch->name = strdup(name);
    free(name); 
    new_merch->description = strdup(description);
    free(description); 
    new_merch->price = price;
    new_merch->stock = stock; 

    return new_merch;
}

static location_t *location_create(char *shelf, int amount)
{
    location_t *location = calloc(1, sizeof(location_t)); 
    location->shelf = strdup(shelf);
    free(shelf);  
    location->quantity = amount; 

    return location; 
}

void store_add(store_t *store, merch_t *merch)
{
    ioopm_hash_table_insert(store, str_elem(merch->name), void_elem(merch)); 
}

static bool shelf_exists(merch_t *merch, char *shelf)
{
    location_t *location = get_location(merch, shelf); 
    if (location == NULL)
    {
        return false; 
    }
    else if (!strcmp(get_shelf(location), shelf))
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

void location_add(merch_t *merch, char *shelf, int amount)
{
    if (shelf_exists(merch, shelf))
    {
        location_t *location = get_location(merch, shelf);
        location->quantity = get_quantity(location) + amount;
        free(shelf);  
    }
    else
    {
        location_t *location = location_create(shelf, amount); 
        ioopm_linked_list_append(merch->stock, void_elem(location)); 
    }
}

bool merch_exists(store_t *store, char *name)
{
    return ioopm_hash_table_has_key(store, str_elem(name)); 
}

bool store_is_empty(store_t *store)
{
    return ioopm_hash_table_is_empty(store);  
}

size_t store_size(store_t *store)
{
    return ioopm_hash_table_size(store);  
}

size_t stock_size(merch_t *merch)
{
    return ioopm_linked_list_size(merch->stock); 
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

char *get_shelf(location_t *location)
{
    if (location == NULL)
    {
        return NULL; 
    }
    else 
    {
        return location->shelf;  
    }
}

int get_quantity(location_t *location)
{
    if (location == NULL)
    {
        return 0; 
    }
    else 
    {
        return location->quantity;  
    }
}

location_t *get_location(merch_t *merch, char *shelf)
{
    if (merch->stock == NULL)
    {
        return NULL; 
    }
    else
    {
        ioopm_list_t *stock = merch->stock; 
        size_t loc_size = stock_size(merch); 

        ioopm_list_iterator_t *iter = ioopm_list_iterator(stock);

        location_t *location = ioopm_iterator_current(iter).void_ptr;
        
        for (int i = 0; i < loc_size; i++)
        {
            if (!strcmp(get_shelf(location), shelf))
            {
                ioopm_iterator_destroy(iter); 
                return location; 
            }
            location = ioopm_iterator_next(iter).void_ptr;
        }
        ioopm_iterator_destroy(iter); 
    }
    return (location_t *) NULL; 
}

static ioopm_list_t *get_stock(merch_t *merch)
{
    return merch->stock;  
}

void set_name(store_t *store, merch_t *old_merch, char *new_name)
{
    int price = get_price(old_merch); 
    char *description = get_description(old_merch); 
    ioopm_list_t *stock = get_stock(old_merch); 

    merch_t *new_merch = merch_create(new_name, description, price, stock); 

    store_add(store, new_merch); 

    char *old_name = get_name(old_merch); 
    ioopm_hash_table_remove(store, str_elem(old_name)); 
    free(old_name);
    free(old_merch); 
}

void set_description(merch_t *merch, char *new_description)
{
    char *old_description = get_description(merch); 
    merch->description = strdup(new_description);
    free(old_description); 
    free(new_description); 
}

void set_price(merch_t *merch, int new_price)
{
    merch->price = new_price; 
}

void print_merch(merch_t *merch)
{
    printf("\nName: %s", get_name(merch)); 
    //printf("\nDescription: %s", get_description(merch)); 
    //printf("\nPrice: %d", get_price(merch)); 
    //print_stock(merch);
}

void print_stock(merch_t *merch)
{
    ioopm_list_t *stock = get_stock(merch); 
    size_t loc_size = stock_size(merch); 

    for (int i = 0; i < loc_size; i++)
    {
        location_t *location = ioopm_linked_list_get(stock, i).void_ptr; 
        printf("\nShelf: %s, Quantity: %d ", location->shelf, location->quantity); 
    }
    puts("\n"); 
}

static void stock_destroy(elem_t *value, void *arg)
{
    char *shelf = get_shelf(value->void_ptr); 
    free(shelf); 
    free(value->void_ptr);
}

void store_remove(store_t *store, char *name)
{
    merch_t *merch = get_merch(store, name); 
    ioopm_list_t *stock = get_stock(merch); 

    ioopm_linked_list_apply_to_all(stock, stock_destroy, NULL); 
    ioopm_linked_list_destroy(stock); 

    ioopm_hash_table_remove(store, str_elem(name)); 
    free(merch->name); 
    free(merch->description); 
    free(merch); 
}

static void merch_destroy(elem_t name, elem_t *value, void *arg)
{
    ioopm_list_t *stock = get_stock(value->void_ptr); 
    ioopm_linked_list_apply_to_all(stock, stock_destroy, NULL); 
    ioopm_linked_list_destroy(stock); 
    char *name_in_merch = get_name(value->void_ptr); 
    char *description = get_description(value->void_ptr); 
    free(name_in_merch); 
    free(description); 
    free(value->void_ptr); //merch 
}

void store_destroy(store_t *store)
{
    ioopm_hash_table_apply_to_all(store, merch_destroy, NULL); 
    ioopm_hash_table_destroy(store); 
}
