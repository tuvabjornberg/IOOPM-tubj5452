#pragma once
#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/iterator.h"

#define INITIAL_CAPACAITY 10

/**
 * @file merch_storage.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief A simple implementation of a storage system for merchendise. 
 * 
 * The code supports creating and managing merch, adding them to the store, editing 
 * and removing items as well as destroying the store all together. 
 * 
 * The body of the store is the store_t type with a hashtable element where a 
 * merch's name maps to its information. 
 *  
 * The hash table assumes a suitable hash_function (hash_fun) and equality function 
 * to fit the ioopm_eq_function in common.h.
 * 
 * Dependencies: hash_table.h, merch_storage.h, hash_fun.h
 * 
 * It is assumed that the user ensures proper memory management after creating and adding 
 * items to the store, as these structures involve dynamic memory allocation.
 */

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

/// @brief creates a new store
/// @return a new empty store
store_t *ioopm_store_create();

/// @brief creates a merch
/// @param name the name of the merch
/// @param description a description of the merch
/// @param price the price of the merch
/// @param stock a list of storage locations
/// @param stock_size the amount of merch on all locations
/// @return a merch
merch_t *ioopm_merch_create(char *name, char *description, int price, ioopm_list_t *stock, int stock_size);

/// @brief adds a merch to the store
/// @param store the store to add merch into
/// @param merch the merch to add into the store expects a valid existing merch
void ioopm_store_add(store_t *store, merch_t *merch); 

/// @brief adds or replenishes a shelf with items of the merch
/// @param merch the merch to add a shelf to, expects a valid existing merch
/// @param shelf the shelf to add or replenish
/// @param amount a number of items to put on the shelf
void ioopm_location_add(merch_t *merch, char *shelf, int amount); 

/// @brief searches the store if a merch exists
/// @param store the store to search, expects a valid existing store
/// @param name the name of the merch to find
/// @return a truth value of if the merch is found
bool ioopm_merch_exist(store_t *store, char *name); 

/// @brief checks if store is emty
/// @param store the store operated upon
/// @return true if the merch count is 0, else false
bool ioopm_store_is_empty(store_t *store); 

/// @brief retrieves a merch from the store
/// @param store the store to search
/// @param name the name of the merch to find
/// @return the merch sought
merch_t *ioopm_merch_get(store_t *store, char *name); 

/// @brief retrievs the price of a merch
/// @param merch the merch operated upon, expects a valid existing merch with a price
/// @return the price of the merch
int ioopm_price_get(merch_t *merch); 

/// @brief edits the name of a merch by copying the old merch and inserting a new
/// @param store the store to insert the new merch
/// @param old_merch the old merch to copy and remove, expects a valid existing merch
/// @param new_name the new name to add to the new merch
/// @param carts a hashtable of carts to replace the old merch with the new
void ioopm_name_set(store_t *store, merch_t *old_merch, char *new_name, ioopm_hash_table_t *carts); 

/// @brief edits the description of a merch
/// @param merch the merch to update, expects a valid existing merch
/// @param new_description the new description to replace
void ioopm_description_set(merch_t *merch, char *new_description); 

/// @brief edits the price of a merch
/// @param merch the merch to update, expects a valid existing merch 
/// @param new_price the new price to replace
void ioopm_price_set(merch_t *merch, int new_price); 

/// @brief prints a merch to the command line
/// @param merch to print, expects a valid existing merch
void ioopm_merch_print(merch_t *merch); 

/// @brief prints the shelves and stock of a merch
/// @param merch print its stock, expects a valid existing merch
void ioopm_stock_print(merch_t *merch); 

/// @brief removes a merch from the store and the carts it's in, as well as free its memory
/// @param store the store to remove from
/// @param carts the carts to remove from
/// @param name the name of the merch to remove
void ioopm_store_remove(store_t *store, ioopm_hash_table_t *carts, char *name);

/// @brief deletes a store and free its memory
/// @param store the store to remove
void ioopm_store_destroy(store_t *store); 