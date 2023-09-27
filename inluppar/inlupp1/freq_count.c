#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

//1. Create an empty hash table
//2. For each file argument, read each word in the file
//   2.1 If the word is not in the hash table
//       2.1.1 Put it there, and give it the value 1
//   2.2 Otherwise
//       2.2.1 Increments its current value by 1
//3. Print the outputs in lexicographic order on the keys
//4. Tear down the hash table, free all resources, close all files


#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmp_stringp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
    qsort(keys, no_keys, sizeof(char *), cmp_stringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
    // FIXME: error-handling, etc. //Rewrite to match your own interface,
    int freq =
        ioopm_hash_table_has_key(ht, (elem_t) {.string = word}) ?
        (ioopm_hash_table_lookup(ht, (elem_t) {.string = word}))->value.integer :
        0;
    ioopm_hash_table_insert(ht, (elem_t) {.string = strdup(word)}, (elem_t) {.integer = freq + 1});
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r"); //!!!!!!!!!!!!!!
    
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

int string_sum_hash(elem_t e)
{
    char *str = e.string;
    int result = 0;
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
    size_t size = ioopm_hash_table_size(ht);

    if (argc > 1)
    {   
        for (int i = 1; i < argc; ++i)
        {
            process_file(argv[i], ht);
        }

        // FIXME: If the keys are returned as a list, transfer them into 
        // an array to use `sort_keys` (perhaps using an iterator?)
        //char **keys = (char **) ioopm_hash_table_keys(ht);

        ioopm_list_iterator_t *iter = ioopm_hash_table_iterator(ht);
        char **keys = (char **)calloc(1, size * sizeof(char *));
        size_t i = 0;

        while (ioopm_iterator_has_next(iter))
        {
            elem_t value = ioopm_iterator_next(iter);
            keys[i++] = value.string;
        }

        sort_keys(keys, size);

        ioopm_iterator_destroy(iter);




        int size = ioopm_hash_table_size(ht);
        sort_keys(keys, size);

        for (int i = 0; i < size; ++i)
        {
            // FIXME: Update to match your own interface, error handling, etc.
            int freq = (ioopm_hash_table_lookup(ht, (elem_t) {.string = keys[i]}))->value.integer;
            printf("%s: %d\n", keys[i], freq);
        }
    }   
    else
    {
        puts("Usage: freq-count file1 ... filen");
    }

    // FIXME: Leaks memory! Use valgrind to find out where that memory is 
    // being allocated, and then insert code here to free it.
    ioopm_hash_table_destroy(ht);
}   

