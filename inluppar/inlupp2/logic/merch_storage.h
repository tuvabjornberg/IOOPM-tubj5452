#include "hash_table.h"
#include "linked_list.h"


/**
 * @file merch_storage.h
 * @author Tuva Björnberg & Marcus Ray Sandersson
 * @date 2/10-2023
 * @brief  
 *
 */


typedef struct {
    char *name;
    char *description;
    int price;
    int stock;
    ioopm_list_t *location;
} merch_t;

typedef ioopm_hash_table_t merch_table_t; 


/// @brief creates a new merch
/// @param
/// @return
merch_t create_merch(char *name, char *description, int price, char *shelf, int stock);

/// @brief 
/// @param
/// @return
void store_add(merch_table_t *store, merch_t merch); 

/// @brief 
/// @param
/// @return
void store_remove(merch_table_t *store, merch_t merch); 

/// @brief 
/// @param
/// @return
bool merch_exists(merch_table_t *store, char *name); 

/// @brief 
/// @param
/// @return
size_t store_size(merch_table_t *store); 

/// @brief 
/// @param
/// @return
merch_t get_merch(merch_table_t *store, char *name); 

/// @brief 
/// @param
/// @return
void get_names_in_arr(merch_table_t *store, char *arr_of_names[]); 

/// @brief 
/// @param
/// @return
int get_stock(char *name); 

/// @brief 
/// @param
/// @return
void set_name(merch_t merch, char *new_name); 

/// @brief 
/// @param
/// @return
void set_description(merch_t merch, char *new_description); 

/// @brief 
/// @param
/// @return
void set_price(merch_t merch, char *new_price); 

/// @brief 
/// @param
/// @return
void print_merch(merch_t merch); 

/// @brief 
/// @param
/// @return
void print_stock(merch_t merch); 

/// @brief 
/// @param
/// @return
bool store_is_empty(merch_table_t *store); 

