#pragma once
#include "merch_storage.h"


/**
 * @file shop_cart.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief  
 *
 */


typedef struct {
    ioopm_hash_table_t *carts; 
    int total_carts; 
} carts_t;


/// @brief 
/// @param hash_fun 
/// @param eq_fun 
/// @return 
carts_t *cart_storage_create(ioopm_hash_function hash_fun, ioopm_eq_function eq_fun); 

/// @brief 
/// @param storage_carts 
/// @param id 
/// @return 
ioopm_hash_table_t *get_items_in_cart(carts_t *storage_carts, int id); 

/// @brief 
/// @param cart_items 
/// @param id 
/// @return 
bool has_merch_in_cart(ioopm_hash_table_t *cart_items, char *name);


/// @brief 
/// @param storage_carts 
void cart_storage_destroy(carts_t *storage_carts);

 


void cart_create(carts_t *storage_carts, ioopm_hash_function hash_fun, ioopm_eq_function eq_fun); 

 


void cart_destroy(carts_t *storage_carts, int id); 

 


bool carts_is_empty(carts_t *storage_carts); 

 
int item_in_cart_amount(carts_t *storage_carts, int id, char *merch_name); 



void cart_add(carts_t *storage_carts, int id, char *merch_name, int amount); 

 


void cart_remove(ioopm_hash_table_t *cart_items, char *merch_name, int amount);
 


int cost_calculate(store_t *store, carts_t *storage_carts, int id);

 


void cart_checkout(carts_t *storage_carts, int id); 

 


void cart_destroy(carts_t *storage_carts, int id); 

