#pragma once

#include <stdbool.h>

#define Successful(o) (o.success == true)
#define Unsuccessful(o) (o.success == false)

/**
 * @file hash_table.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 11/09-2023
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */

typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t; 

struct option
{
  bool success;
  char *value;
};

/// @brief create a new hash table
/// @return a new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return an option with an is found bool and a value
option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);

/// @brief delete an option and free its memory
/// @param option option with success and value 
void ioopm_destroy_option(option_t *option_found); 