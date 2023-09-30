#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmp_stringp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
    qsort(keys, no_keys, sizeof(char *), cmp_stringp);
}

static void free_keys(elem_t key, elem_t *value_ignored, void *extra)
{
    free(key.string); 
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
    option_t *lookup_result = ioopm_hash_table_lookup(ht, (elem_t) {.string = word}); 

    int freq =
        ioopm_hash_table_has_key(ht, (elem_t) {.string = word}) ?
        lookup_result->value.integer :
        0;

    if (lookup_result->success)
    {
        ioopm_hash_table_insert(ht, (elem_t) {.string = word}, (elem_t) {.integer = freq + 1}); 
    }
    else
    {
        char *dup_word = strdup(word); 
        ioopm_hash_table_insert(ht, (elem_t) {.string = dup_word}, (elem_t) {.integer = freq + 1}); 
    }

    free(lookup_result);
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r"); 
    
    while (true)
    {
        char *buf = NULL;
        size_t len = 0;
        getline(&buf, &len, f);

        if (feof(f))
        {
            free(buf);
            break;
        }

        for (char *word = strtok(buf, Delimiters);
            word && *word;
            word = strtok(NULL, Delimiters))
        {
            process_word(word, ht);
        }

        free(buf);
    }
    
    fclose(f);
}

unsigned string_sum_hash(elem_t e)
{
    char *str = e.string;
    unsigned result = 0;
    do
    {
        result += *str;
    }
    while (*++str != '\0');
    return result; 
}

bool string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.string, e2.string) == 0);
}

int main(int argc, char *argv[])
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create((ioopm_hash_function) string_sum_hash, string_eq);
    
    if (argc > 1)
    {   
        for (int i = 1; i < argc; ++i)
        {
            process_file(argv[i], ht);
        }
        
        size_t ht_size = ioopm_hash_table_size(ht); 

        ioopm_list_t *list = ioopm_hash_table_keys(ht);
        size_t list_size = ioopm_linked_list_size(list);

        ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
        elem_t value = ioopm_iterator_current(iter);
   
        char *keys[list_size]; 

        for (int i = 0; i < list_size; i++)
        {
            keys[i] = value.string;
            value = ioopm_iterator_next(iter);
        }
           
        sort_keys(keys, ht_size);

        for (int i = 0; i < ht_size; i++)
        {
            option_t *lookup_result = ioopm_hash_table_lookup(ht, (elem_t) {.string = keys[i]}); 
            
            int freq = lookup_result->value.integer;        
            printf("%s: %d\n", keys[i], freq);
            free(lookup_result); 
        }
        
        ioopm_hash_table_apply_to_all(ht, free_keys, NULL);
        ioopm_linked_list_destroy(list); 
        ioopm_iterator_destroy(iter);
    }   
    else
    {
        puts("Usage: freq-count file1 ... filen");
    }

    ioopm_hash_table_destroy(ht);
}   
