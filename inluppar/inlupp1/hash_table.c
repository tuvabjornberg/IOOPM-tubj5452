#include <stdlib.h>
#include "hash_table.h"
#include <stdio.h>
#include <stdbool.h>

#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};

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
  entry_t buckets[17];
};

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

/*
static void entry_destroy_recursive(entry_t *entry)
{
  if (entry != NULL)
  {
    entry_destroy(entry->next);
    free(entry);
  }
}
*/

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
  for (int i = 0; i < 17; i++) // CHEAT/TODO: hardcoded, implement something general //ht != NULL
  { 
    entry_destroy((&ht->buckets[i])->next);
  }
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
  //unsigned bucket_index = key < 0 ? 0 : key % 17;
  //entry_t *sentinel = entry_create(0, "invalid", bucket); 

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
  int bucket = key % 17;
  
  /// Search for an existing entry for a key 
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
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

void ioopm_destroy_option(option_t *option_found) {
    free(option_found); 
}

option_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  unsigned bucket_index = key < 0 ? 0 : key % 17;

  option_t *result = calloc(1, sizeof(option_t)); 
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket_index], key);
  entry_t *next = tmp->next;

  if (next != NULL)
    {
      *result = Success(next->value);
    }
  else
    {
      *result = Failure();
    }
    return result; 
}