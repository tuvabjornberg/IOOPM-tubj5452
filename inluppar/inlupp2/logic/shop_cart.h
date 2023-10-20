#pragma once
#include "merch_storage.h"

/**
 * @file shop_cart.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief  A simple implementation of a shopping cart system. 
 * 
 * The code supports creating and managing shopping carts, adding and removing items,
 * calculating the total cost of items in a cart, and checking out a cart.
 * 
 * The main structure is the carts_t type, which includes a hash table where cart IDs
 * map to the items in the cart. Each cart is represented by a hash table where merch
 * names map to the quantity of each item.
 * 
 * The hash table assumes a suitable hash_function (hash_fun) and equality function 
 * to fit the ioopm_eq_function in common.h.
 * 
 * Dependencies: hash_table.h, merch_storage.h, hash_fun.h
 * 
 *  It is assumed that the user ensures proper memory management after creating and 
 * manipulating shopping carts, as these structures involve dynamic memory allocation.
 *
 */

typedef struct {
    ioopm_hash_table_t *carts; 
    int total_carts; 
} carts_t;

/// @brief creates a shopping cart storage
/// @return a new empty storage
carts_t *ioopm_cart_storage_create(); 

/// @brief creates a new cart
/// @param storage_carts the storage to add the new cart to, expects a valid existing storage_carts
void ioopm_cart_create(carts_t *storage_carts); 

/// @brief retrieves the items of a cart
/// @param storage_carts the storage to get the cart from, expects a valid existing storage_carts
/// @param id the id of the cart sought
/// @return the items of the cart
ioopm_hash_table_t *ioopm_items_in_cart_get(carts_t *storage_carts, int id); 

/// @brief checks if a merch exists in a cart
/// @param cart_items a cart's items to search, expects a valid existing cart
/// @param name the name of the merch to find
/// @return true if merch is in cart, else false
bool ioopm_has_merch_in_cart(ioopm_hash_table_t *cart_items, char *name);

/// @brief checks if the cart storage has carts
/// @param storage_carts the storage operated upon
/// @return true if there are no carts, else false
bool ioopm_carts_are_empty(carts_t *storage_carts); 
 
/// @brief finds the amount of one item in a cart
/// @param storage_carts the storage to find the cart from
/// @param id the id of the cart to find the merch
/// @param merch_name the merch name of the merch to find the amount from
/// @return the amount of said merch in the speicifc cart
int ioopm_item_in_cart_amount(carts_t *storage_carts, int id, char *merch_name); 

/// @brief adds an item to a cart
/// @param storage_carts the storage to find the cart from
/// @param id the id of the cart to add the item to
/// @param merch_name the name of the merch to add
/// @param amount the ampunt of said merch to add
void ioopm_cart_add(carts_t *storage_carts, int id, char *merch_name, int amount); 

/// @brief removes one or more of a merch from a cart 
/// @param cart_items the items of a cart
/// @param merch_name the name of the merch to remove quantities of
/// @param amount the quantity to remove
void ioopm_cart_remove(ioopm_hash_table_t *cart_items, char *merch_name, int amount);
 
/// @brief calculates the cost of all items in a cart
/// @param store the store to find the merch from
/// @param storage_carts the cart storage to find the cart from
/// @param id the id of the cart to be operated upon
/// @return the total cost of the current items
int ioopm_cost_calculate(store_t *store, carts_t *storage_carts, int id);

/// @brief checks out a cart from the store adn decreases its stock
/// @param storage_carts the storage carts to find the cart from
/// @param id the id of the cart to checkout
void ioopm_cart_checkout(carts_t *storage_carts, int id); 

/// @brief destroys a cart and frees its memory
/// @param storage_carts the cart storage to remove cart from
/// @param id the id of the cart to destroy
void ioopm_cart_destroy(carts_t *storage_carts, int id); 

/// @brief deletes a cart storage and frees its memory
/// @param storage_carts the storage to remove
void ioopm_cart_storage_destroy(carts_t *storage_carts);