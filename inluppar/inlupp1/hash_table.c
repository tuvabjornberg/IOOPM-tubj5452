#include <stdlib.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};

/// the types from abovem  
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  ioopm_hash_function hash_fun;
};

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun)
{
  /// Allocate space for a ioopm_hash_table_t = No_Buckets (17) pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
  ht->hash_fun = hash_fun;
  return ht;
}

static void entry_destroy(entry_t *entry)
{
  while (entry != NULL)
  {
    entry_t *next = entry->next;
    free(entry);
    entry = next;
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht); 
  free(ht);
}

// Creates a new entry with a given key, value and next pointer
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
}

static entry_t *find_previous_entry_for_key(entry_t *bucket, int key)
{
  entry_t *prev = bucket;
  entry_t *current = bucket->next;

  while (current != NULL && current->key.integer != key)
  {
    prev = current;
    current = current->next;
  }

  return prev;

/*

  if (*address == NULL)
    {
      return NULL;
    }
  else
    {
      entry_t *first_entry = *address;
      entry_t *next_entry = first_entry->next;
      entry_t **result = address;
      
      if (compare_key(key, (elem_t) {.void_ptr = NULL}, &first_entry->key))
        {
          return result;
        }
      
      while (next_entry != NULL)
        {
          if (compare_key(key, (elem_t) {.void_ptr = NULL}, &next_entry->key))
            {
              return result;
            }
          result = &next_entry;
          next_entry = next_entry->next;
        }
      
      return NULL;
    }
    */
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  /// Calculate the bucket for this entry
  int bucket_index = key.integer < 0 ? 0 : ht->hash_fun(key);;

  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket_index], key.integer);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key.integer == key.integer)
  {
    next->value = value;
  }
  else
  {
    entry->next = entry_create(key, value, next);
  }
}

option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  int bucket_index = key.integer < 0 ? 0 : ht->hash_fun(key);;

  option_t *lookup_result = calloc(1, sizeof(option_t));
  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key.integer);
  entry_t *current = prev->next;

  if (current != NULL)
  {
    *lookup_result = Success(current->value);
  }
  else
  {
    *lookup_result = Failure();
  }

  return lookup_result;

  //  int bucket = ht->hash_function(key);
  //modulo(&bucket, ht->buckets_size);
  
  //entry_t **entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_func);
  //if (entry == NULL)
  //  {
  //    return NULL;
  //  }
  //else
  //  {
  //    return &(*entry)->value;
  //  }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  int bucket_index = key.integer < 0 ? 0 : ht->hash_fun(key);;

  option_t *lookup_result = ioopm_hash_table_lookup(ht, key);

  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key.integer);
  entry_t *current = prev->next;
  elem_t removed_value; 

  if (lookup_result->success)
  {
    removed_value = current->value;

    if (current->next == NULL)
    {
      // for last entries
      prev->next = NULL;
      free(current);
    }
    else
    {
      // for first and middle entries
      prev->next = current->next;
      free(current);
    }
  }
  else
  {
    //error handeling
    removed_value.string = "key does not have an entry";
    //removed_value = -1; 
  }

  free(lookup_result);
  return removed_value;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) 
{
  int counter = 0; 
  for (int i = 0; i < No_Buckets; i++) // CHEAT/TODO: hardcoded, implement something general //*ht != NULL
  {
    entry_t *cursor = &ht->buckets[i]; 
    counter++; 
    while (cursor->next != NULL)
    {
      counter++; 
      cursor = cursor->next; 
    }
  }
  return counter;  
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *cursor = &ht->buckets[i]; 
    if (cursor->next != NULL)
    {
      return false; 
    }
  }
  
  return true;   
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; i++) // CHEAT/TODO: hardcoded, implement something general //*ht != NULL
  {
    entry_destroy((&ht->buckets[i])->next);
    ht->buckets[i].next = NULL; //reset all dangling pointers 
  }
}

static bool bool_eq_fun(elem_t a, elem_t b) 
{
    return b.integer == a.integer; 
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create(bool_eq_fun);

  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next; 
    while (current != NULL)
    {
      ioopm_linked_list_append(list, current->key); 
      current = current->next; 
    }
  }
  return list;  
}

char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  char **array_of_values = calloc(1, sizeof(char *) * ioopm_hash_table_size(ht)); 
  int index = 0; 

  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next; 
    while (current != NULL)
    {
      array_of_values[index] = current->value.string; 
      current = current->next; 
      index++; 
    }
  }
  array_of_values[index] = NULL; //last pointer to use as an end marker

  return array_of_values;   
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  option_t *lookup_result = ioopm_hash_table_lookup(ht, key);

  if (lookup_result->success)
  {
    free(lookup_result); 
    return true; 
  } 
  else
  {
    free(lookup_result); 
    return false; 
  }
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next; 
    
    while (current != NULL)
    {
      char *duplicate = strdup(current->value.string); 

      //test using both the identical string and the equivalent string 
      if (!strcmp(current->value.string, value.string) && !strcmp(duplicate, value.string) && current->value.string == value.string)
      {
        free(duplicate); 
        return true; 
      }
      
      free(duplicate); 
      current = current->next; 
    }
  }
  return false; 
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      if (pred(current->key, current->value, arg)) 
      {
        return true;
      }
      current = current->next;
    } 
  }
  return false;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;

    while (current != NULL) 
    {
      if (!pred(current->key, current->value, arg)) 
      {
        return false;
      }
      current = current->next;
    } 
  }
  return true;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next;
  
  while (current != NULL) 
  {
    apply_fun(current->key, current->value, arg); // address of value to apply function
    current = current->next;
    }
  }
}


