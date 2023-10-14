#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hash_table.h"
#include <CUnit/Basic.h>
#include <stdbool.h>
#include "linked_list.h"
#include "common.h"
#include <assert.h>


#define No_Buckets 17

typedef struct entry entry_t;

typedef struct hash_table ioopm_hash_table_t;


struct entry
{
  elem_t key;       
  elem_t value;   
  entry_t *next; 
};

struct hash_table
{
  entry_t *buckets[No_Buckets];
  ioopm_hash_function hash_function;
  cmp_fun_t comp_fun;
  ioopm_eq_function eq_key;
  ioopm_eq_function eq_value;
};

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next) 
{
  entry_t *create = calloc(1,sizeof(entry_t));
  create->key = key;
  create->value = value;
  create->next = next;
  return create;
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash, cmp_fun_t comp_fun , ioopm_eq_function eq_key, ioopm_eq_function eq_value)
{
  ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));

  for(int i = 0; i < No_Buckets; i ++) 
  { 
    ht->buckets[i] = entry_create(int_elem(0), (elem_t) {.p = NULL} , NULL);
  }
  ht->hash_function = hash;
  ht->eq_key = eq_key;
  ht->eq_value = eq_value;
  ht->comp_fun = comp_fun;

  return ht;      
}

void entry_destroy(ioopm_hash_table_t *ht) 
{
  
  for(int i = 0; i < No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    
    while (cursor != NULL) {
      entry_t *next = cursor->next;
      free(cursor);
      cursor = next;
    }
      free(ht->buckets[i]);
  }
}


static entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key, ioopm_eq_function eq_fun, cmp_fun_t comp_fun) 
{
  assert(entry != NULL);
  entry_t *cursor = entry;
    while (cursor->next != NULL)
    {
        if (comp_fun(cursor->next->key, key) || eq_fun(cursor->next->key, key))
        {
            return cursor;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return cursor;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  assert(ht != NULL);
  int bucket = ht->hash_function(key);

  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key, ht->eq_key, ht->comp_fun);
  entry_t *next = entry->next;
  
  if (next != NULL && ht->eq_key(next->key, key))
    {
      next->value = value;
    }
  else 
    {
      entry->next = entry_create(key, value, next);
    }
}



void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  assert(ht != NULL);
  entry_destroy(ht);
  free(ht);
}

elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  assert(ht != NULL);
  int bucket = ht->hash_function(key);

  entry_t *tmp = find_previous_entry_for_key(ht->buckets[bucket], key, ht->eq_key, ht->comp_fun);
  entry_t *next = tmp->next;

    if (next != NULL && ht->eq_key(next->key, key))
    {
     
      return &next->value;
    }
  else
    {
      return NULL; 
    }
  }
  


elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key) 
{
  assert(ht != NULL);
  int bucket = ht->hash_function(key);

  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key, ht->eq_key, ht->comp_fun);
  entry_t *next = entry->next;

  if (next != NULL && ht->eq_key(next->key, key))
    {
      entry->next = next->next;
      elem_t tmp = entry->value;
      free(next);
     
      return tmp;
    } else {

      return (elem_t) {.p = NULL};
    }
}


size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) 
{
  assert(ht != NULL);
  int count = 0;
  for (int i = 0; i < No_Buckets; i++)
  {
    entry_t *buckets = ht->buckets[i];
    entry_t *cursor = buckets->next;
    while (cursor != NULL)
    {
      count++;
      cursor = cursor->next;
    }
    
  }
  return count;
  
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);
  return ioopm_hash_table_size(ht) == 0;
}



void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);
  if(ioopm_hash_table_is_empty(ht)) {
    return;  

  } else {
    for(int i = 0; i < No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;

    while (cursor != NULL) {
      entry_t *next = cursor->next;
      free(cursor);
      cursor = next;
      }
      ht->buckets[i]->next = NULL;
    }
  }
}


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);
  ioopm_list_t *keys = ioopm_linked_list_create(compare_ints);

  if (keys == NULL) {
  } else {
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    
    while (cursor != NULL) {
      ioopm_linked_list_append(keys, cursor->key);
      cursor = cursor->next;
    }
  }
}
  return keys;

}


ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);
  ioopm_list_t *values = ioopm_linked_list_create(compare_strings);

   if (values == NULL) {
  } else {
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *cursor = ht->buckets[i]->next;
    
    while (cursor != NULL) {
      ioopm_linked_list_append(values, cursor->value);
      cursor = cursor->next;
      }
    }
  }

  return values;
}

typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

static bool key_equiv(elem_t key, elem_t value, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  
  return key.integer == other_key;
}

static bool value_equiv(elem_t key, elem_t value, void *x)
{
  char **other_value_ptr = x;
  char *other_value = *other_value_ptr;

  if(strcmp(value.string, other_value) == 0){
    return true;
  }

  return false;
}



bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  assert(ht != NULL);
    for (int i = 0; i < No_Buckets; ++i) {
      
      entry_t *cursor = ht->buckets[i]->next;
      while (cursor != NULL) {
        elem_t key = cursor->key;
        elem_t value = cursor->value;
        if (!pred(key, value, arg)) {
            return false;
        }
        cursor = cursor->next;
        }
    }
      return true;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg) 
{
  assert(ht != NULL);
    for (int i = 0; i < No_Buckets; ++i) {
      
      entry_t *cursor = ht->buckets[i]->next;
      while (cursor != NULL) {
        elem_t key = cursor->key;
        elem_t value = cursor->value;
        if (pred(key, value, arg)) {
            return true;
        }
          cursor = cursor->next;
        }
       }
        return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg) {
  assert(ht != NULL);
    for (int i = 0; i < No_Buckets; ++i) {
      
      entry_t *cursor = ht->buckets[i]->next;

      while (cursor != NULL) {
        apply_fun(cursor->key, &cursor->value, arg);
        cursor = cursor->next;
        }
    }

}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t *value) 
{
  return ioopm_hash_table_any(ht, value_equiv, value);
}


elem_t *create_elem_t_string(char *str)
{
    elem_t *value = calloc(1, sizeof(elem_t));
    if (value != NULL) {
        value->string = str;
    }
    return value;
}


bool eq_int_elements(elem_t a, elem_t b)
{
  return a.integer == b.integer;
}

bool eq_string_elements(elem_t a, elem_t b) 
{
  return strcmp((char *)a.p, (char *)b.p) == 0;
}


bool compare_ints(elem_t point, elem_t key)
{
    return  key.integer - point.integer < 0;
}


bool compare_strings(elem_t point, elem_t key)
{
    return strlen((char *)key.p) - strlen((char *)point.p) < 0;
}


int ht_func_strings(elem_t key)
{
    int value = 0;
    char *str = (char *)key.p;
    for (int i = 0; i < strlen(str); i++)
    {
        value += str[i];
    }
    return value % No_Buckets;
}


int ht_func_int(elem_t key)
{
    return abs(key.integer) % No_Buckets;
}
















