#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"
#include "merch_storage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

store_t *store_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun)
{
  store_t *new_store = calloc(1, sizeof(store_t));
  new_store->merch_names = calloc(10, sizeof(char*));
  new_store->merch_details = ioopm_hash_table_create(hash_fun, eq_fun);
  new_store->merch_count = 0;
  return new_store;
}

bool location_eq(elem_t a, elem_t b){
  return !strcmp((*(location_t*)a.void_ptr).shelf, (*(location_t*)b.void_ptr).shelf);
}

merch_t *merch_create(char *name, char *description, int price, ioopm_list_t *locations)
{
  merch_t *new_merch = calloc(1, sizeof(merch_t));
  new_merch->name = name;
  new_merch->description = description;
  new_merch->price = price;
  new_merch->locations = ioopm_linked_list_create(location_eq);

  return new_merch;
}

//Gets index of element in names array if it exists else gets index where it would be
static int names_index_of(store_t *store, char *name) {
  char **start = store->merch_names;
  char **end = store->merch_names + store->merch_count-1;
  char **center = store->merch_names + store->merch_count/2;
  
  while(strcmp(*center, name)){
    if(strcmp(name, *start) < 0) return 0;
    if(strcmp(name, *end) > 0) return end - store->merch_names + 1;

    bool is_larger = strcmp(name, *center) > 0;
    start = is_larger ? center + 1 : start;
    end = is_larger ? end : center - 1;
    center = start + (end - start)/2;
  }
  return center - store->merch_names;
}

//inserts in names array at given index, doubles memory allocation of array if overflow
static void names_insert(store_t *store, int index, char *name){
  int last = store->merch_count;
  if(last*sizeof(char*) >= sizeof(store->merch_names)){
    char **tmp = store->merch_names;
    store->merch_names = calloc(last*2, sizeof(char*));
    for(int i = 0; i < last*2; i++){
      store->merch_names[i] = tmp[i];
    }
  }  
  while(last != index){
    store->merch_names[last] = store->merch_names[last-1];
    last--;
  }
  store->merch_names[index] = name;
}
static void names_remove(store_t *store, int index) {
    int last = store->merch_count - 1;

    //    free(store->merch_names[index]);

    for (int i = index; i < last; i++) {
        store->merch_names[i] = store->merch_names[i + 1];
    }
    store->merch_names[last] = NULL;
}

void store_add(store_t *store, merch_t *merch)
{
  ioopm_hash_table_insert(store->merch_details, str_elem(merch->name), (elem_t){.void_ptr = merch});
  int index = store->merch_count == 0 ? 0 : names_index_of(store, merch->name);
  names_insert(store, index, merch->name);
  store->merch_count++;
}
static location_t *location_create(char *shelf, int amount)
{
    location_t *location = calloc(1, sizeof(location_t)); 
    location->shelf = shelf; 
    location->quantity = amount; 
    return location; 
}

static bool shelf_exists(merch_t *merch, char *shelf)
{
    location_t *location = get_location(merch, shelf); 
    if (get_shelf(location) == shelf)
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
    }
    else
    {
        location_t *location = location_create(shelf, amount); 
        ioopm_linked_list_append(merch->locations, void_elem(location)); 
    }
    return; 
}

bool merch_exists(store_t *store, char *name)
{
  if(store->merch_count == 0) return false;
  char **start = store->merch_names;
  char **end = store->merch_names + store->merch_count-1;
  char **center = store->merch_names + store->merch_count/2;
  
  while(strcmp(*center, name)){
    if(strcmp(name, *start) < 0 || strcmp(name, *end) > 0) return false;

    bool is_larger = strcmp(name, *center) > 0;
    start = is_larger ? center + 1 : start;
    end = is_larger ? end : center - 1;
    center = start + (end - start)/2;
  }
  return true;
}

bool store_is_empty(store_t *store)
{
    return store->merch_count == 0;  
}

size_t store_size(store_t *store)
{
  return store->merch_count;
}


merch_t *get_merch(store_t *store, char *name)
{
  option_t *lookup_result = ioopm_hash_table_lookup(store->merch_details, str_elem(name));

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
size_t locations_size(merch_t *merch)
{
    return ioopm_linked_list_size(merch->locations); 
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
    if (merch->locations == NULL)
    {
        return NULL; 
    }
    else
    {
        ioopm_list_t *locations = merch->locations; 
        size_t loc_size = locations_size(merch); 

        ioopm_list_iterator_t *iter = ioopm_list_iterator(locations);

        location_t *location = ioopm_iterator_current(iter).void_ptr;
        
        for (int i = 0; i < loc_size; i++)
        {
            if (get_shelf(location) == shelf)
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

static ioopm_list_t *get_locations(merch_t *merch)
{
    return merch->locations;  
}


void set_name(store_t *store, merch_t *old_merch, char *new_name)
{
    int price = get_price(old_merch); 
    char *description = get_description(old_merch); 
    ioopm_list_t *locations = get_locations(old_merch); 

    merch_t *new_merch = merch_create(new_name, description, price, locations); 

    store_add(store, new_merch); 

    char *old_name = get_name(old_merch); 
    free(old_merch);
    ioopm_hash_table_remove(store->merch_details, str_elem(old_name)); 
}

void set_description(merch_t *merch, char *new_description)
{
    merch->description = new_description;
}

void set_price(merch_t *merch, int new_price)
{
    merch->price = new_price; 
}

void print_merch(merch_t *merch)
{
    printf("\nName: %s", get_name(merch)); 
    printf("\nDescription: %s", get_description(merch)); 
    printf("\nPrice: %d", get_price(merch)); 
    print_stock(merch);
}

void print_stock(merch_t *merch)
{
    ioopm_list_t *locations = get_locations(merch); 
    size_t loc_size = locations_size(merch); 

    for (int i = 0; i < loc_size; i++)
    {
        location_t *location = ioopm_linked_list_get(locations, i).void_ptr; 
        printf("\nShelf: %s, Quantity: %d ", location->shelf, location->quantity); 
    }
}

static void locations_destroy(elem_t *value, void *arg)
{
    free(value->void_ptr);
}

void store_remove(store_t *store, char *name)
{
    merch_t *merch = get_merch(store, name); 
    ioopm_list_t *locations = get_locations(merch); 

    ioopm_linked_list_apply_to_all(locations, locations_destroy, NULL); 
    ioopm_linked_list_destroy(locations);
    names_remove(store, names_index_of(store, name));

    free(merch); 
    ioopm_hash_table_remove(store->merch_details, str_elem(name));
    store->merch_count--;
}

static void merch_destroy(elem_t name, elem_t *value, void *arg)
{
    ioopm_list_t *locations = get_locations(value->void_ptr); 
    ioopm_linked_list_apply_to_all(locations, locations_destroy, NULL); 
    ioopm_linked_list_destroy(locations); 
    free(value->void_ptr); 
}

void store_destroy(store_t *store)
{
    ioopm_hash_table_apply_to_all(store->merch_details, merch_destroy, NULL);
    //TODO: destroy store->merch_names
    ioopm_hash_table_destroy(store->merch_details); 
}
