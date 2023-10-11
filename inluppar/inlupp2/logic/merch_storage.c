#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
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

merch_t *merch_create(char *name, char *description, int price, char *shelf)
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

void store_add(store_t *store, merch_t *merch)
{
  ioopm_hash_table_insert(store->merch_details, str_elem(merch->name), (elem_t){.void_ptr = merch});
  int index = store->merch_count == 0 ? 0 : names_index_of(store, merch->name);
  names_insert(store, index, merch->name);
  store->merch_count++;
}

void stock_add(merch_t *merch, int to_add)
{
    return; 
}

void location_add(merch_t *merch, char *shelf)
{
    return; 
}

void store_remove(store_t *store, merch_t *merch)
{
    return; 
} 

void location_remove(merch_t *merch, char *shelf)
{
    return; 
}


bool merch_exists(store_t *store, char *name)
{
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

bool shelf_exists(merch_t *merch, char *shelf)
{
    return false; 
}


bool store_is_empty(store_t *store)
{
    return store->merch_count == 0;  
}

size_t store_size(store_t *store)
{
    return 0; 
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

void get_names_in_arr(store_t *store, char *arr_of_names[])
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


void store_destroy(store_t *store)
{
    ioopm_hash_table_apply_to_all(store, merch_destroy, NULL); 
    ioopm_hash_table_destroy(store); 
}
