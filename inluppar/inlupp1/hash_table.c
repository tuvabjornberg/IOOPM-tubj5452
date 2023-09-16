#include <stdlib.h>
#include "hash_table.h"
#include <stdio.h>
#include <stdbool.h>

#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};

#define No_Buckets 17 //set only for debugging purposes

/// the types from above
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
};

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = No_Buckets (17) pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
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
static entry_t *entry_create(int key, char *value, entry_t *next)
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

  while (current != NULL && current->key != key)
  {
    prev = current;
    current = current->next;
  }

  return prev;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket_index = key < 0 ? 0 : key % No_Buckets;

  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket_index], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
  {
    next->value = value;
  }
  else
  {
    entry->next = entry_create(key, value, next);
  }
}

option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  int bucket_index = key < 0 ? 0 : key % No_Buckets;

  option_t *lookup_result = calloc(1, sizeof(option_t));
  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key);
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
}

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  int bucket_index = key < 0 ? 0 : key % No_Buckets;

  option_t *lookup_result = ioopm_hash_table_lookup(ht, key);

  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket_index], key);
  entry_t *current = prev->next;

  char *removed_value = 0;

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
    removed_value = "key does not have an entry";
  }

  free(lookup_result);
  return removed_value;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht) 
{
  int counter = 0; 
  for (int i = 0; i < No_Buckets; i++) 
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

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *array_of_keys = calloc(1, sizeof(int) * ioopm_hash_table_size(ht)); 
  int index = 0; 

  for (int i = 0; i < No_Buckets; i++) 
  {
    entry_t *current = (&ht->buckets[i])->next; 
    while (current != NULL)
    {
      array_of_keys[index] = current->key; 
      current = current->next; 
      index++; 
    }
  }
  return array_of_keys;  
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
      array_of_values[index] = current->value; 
      current = current->next; 
      index++; 
    }
  }
  array_of_values[index] = NULL; //last pointer to use as an end marker

  return array_of_values;   
}