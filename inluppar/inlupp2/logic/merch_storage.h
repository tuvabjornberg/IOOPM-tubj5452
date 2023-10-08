#include "../data_structures/hash_table.h"
#include "../data_structures/linked_list.h"


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
    ioopm_list_t *locations;
} merch_t;

typedef struct {
  char *shelf;
  int quantity;
} location_t;

typedef ioopm_hash_table_t store_t;

/// @brief creates a new merch
/// @param
/// @return
merch_t create_merch(char *name, char *description, int price, char *shelf, int stock);

/// @brief 
/// @param
/// @return
void store_add(store_t *store, merch_t merch); 

/// @brief 
/// @param
/// @return
void stock_add(merch_t merch, int to_add); 

/// @brief 
/// @param
/// @return
void location_add(merch_t merch, char *shelf); 

/// @brief 
/// @param
/// @return
void store_remove(store_t *store, merch_t merch); 

/// @brief 
/// @param
/// @return
bool merch_exists(store_t *store, char *name); 

/// @brief 
/// @param
/// @return
size_t store_size(store_t *store); 

/// @brief 
/// @param
/// @return
merch_t get_merch(store_t *store, char *name); 

/// @brief 
/// @param
/// @return
void get_names_in_arr(store_t *store, char *arr_of_names[]); 

/// @brief 
/// @param
/// @return
int get_stock(char *name); 

/// @brief may need to insert again to get a valid hashing TODO: edit to better breif
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
void set_price(merch_t merch, int new_price); 

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
bool store_is_empty(store_t *store); 

