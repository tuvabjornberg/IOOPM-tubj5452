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
carts_t *ioopm_cart_storage_create(); 

/// @brief 
/// @param storage_carts 
/// @param id 
/// @return 
ioopm_hash_table_t *ioopm_items_in_cart_get(carts_t *storage_carts, int id); 

/// @brief 
/// @param cart_items 
/// @param id 
/// @return 
bool ioopm_has_merch_in_cart(ioopm_hash_table_t *cart_items, char *name);


/// @brief 
/// @param storage_carts 
void ioopm_cart_storage_destroy(carts_t *storage_carts);

 

/// @brief 
/// @param storage_carts 
/// @param hash_fun 
/// @param eq_fun 
void ioopm_cart_create(carts_t *storage_carts); 

 

/// @brief 
/// @param storage_carts 
/// @param id 
void ioopm_cart_destroy(carts_t *storage_carts, int id); 

 


bool ioopm_carts_are_empty(carts_t *storage_carts); 

 
int ioopm_item_in_cart_amount(carts_t *storage_carts, int id, char *merch_name); 



void ioopm_cart_add(carts_t *storage_carts, int id, char *merch_name, int amount); 

 


void ioopm_cart_remove(ioopm_hash_table_t *cart_items, char *merch_name, int amount);
 


int ioopm_cost_calculate(store_t *store, carts_t *storage_carts, int id);

 


void ioopm_cart_checkout(carts_t *storage_carts, int id); 

 


void ioopm_cart_destroy(carts_t *storage_carts, int id); 

