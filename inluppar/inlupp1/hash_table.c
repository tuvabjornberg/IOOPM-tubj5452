#include <stdlib.h>
#include "hash_table.h"

/// the types from above
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

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

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  free(ht);
}

static entry_t *find_previous_entry_for_key(entry_t *bucket, int key) {
    entry_t dummy; 
    dummy.key = -1;
    dummy.next = bucket;

    entry_t *prev = &dummy;
    entry_t *current = bucket;

    while (current != NULL && current->key != key)
    {
        prev = current;
        current = current->next;
    }

    return prev;
}

// Creates a new entry with a given key, value and next pointer
static entry_t *entry_create(int key, char *value, entry_t *next) {
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  if (new_entry != NULL) {
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = next;
  } 
  
  return new_entry; 
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

char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) {
  return NULL; 
}

