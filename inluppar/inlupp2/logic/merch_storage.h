#pragma once
#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"

/**
 * @file merch_storage.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief  
 *
 */

#define INITIAL_CAPACAITY 10

typedef void(*ioopm_cart_apply_function)(elem_t key, elem_t *value, void *arg1, void *arg2);
typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;

typedef struct {
    char *name;
    char *description;
    int price;
    ioopm_list_t *stock;
    int stock_size;
  int reserved_stock;
} merch_t;

typedef struct {
  char *shelf;
  int quantity;
} location_t;

typedef struct {
  char **merch_names;
  ioopm_hash_table_t *merch_details;
  int merch_count;
  int capacity;
} store_t;

struct entry
{
  elem_t key;      
  elem_t value;   
  entry_t *next; 
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  ioopm_hash_function hash_fun;
  ioopm_eq_function eq_fun; 
};


store_t *ioopm_store_create();


merch_t *ioopm_merch_create(char *name, char *description, int price, ioopm_list_t *stock, int stock_size);


void ioopm_store_add(store_t *store, merch_t *merch); 


void ioopm_location_add(merch_t *merch, char *shelf, int amount); 


bool ioopm_merch_exist(store_t *store, char *name); 


bool ioopm_store_is_empty(store_t *store); 


merch_t *ioopm_merch_get(store_t *store, char *name); 


int ioopm_price_get(merch_t *merch); 


void ioopm_name_set(store_t *store, merch_t *old_merch, char *new_name, ioopm_hash_table_t *carts); 


void ioopm_description_set(merch_t *merch, char *new_description); 


void ioopm_price_set(merch_t *merch, int new_price); 

/// @brief 
/// @param merch to print, expects merch following its struct
/// @return
void ioopm_merch_print(merch_t *merch); 

/// @brief 
/// @param merch print its stock, expects merch following its struct
/// @return
void ioopm_stock_print(merch_t *merch); 


void ioopm_store_remove(store_t *store, ioopm_hash_table_t *carts, char *name);


void ioopm_store_destroy(store_t *store); 
