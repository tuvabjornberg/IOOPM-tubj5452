#include <CUnit/Basic.h>
#include "hash_table.h"
#include <stdbool.h>
#include <stdlib.h>

int init_suite(void)
{
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}

int clean_suite(void)
{
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int invalid_key = -1;

    int key1 = 1;
    int key2 = 18;

    ioopm_hash_table_insert(ht, key1, "value1");
    ioopm_hash_table_insert(ht, key2, "value2");

    // Test existing key1
    option_t *lookup_result = ioopm_hash_table_lookup(ht, key1);

    CU_ASSERT_TRUE(Successful((*lookup_result)));
    CU_ASSERT_STRING_EQUAL("value1", lookup_result->value);
    free(lookup_result);

    // Test existing key2
    lookup_result = ioopm_hash_table_lookup(ht, key2);
    CU_ASSERT_TRUE(Successful((*lookup_result)));
    CU_ASSERT_STRING_EQUAL("value2", lookup_result->value);
    free(lookup_result);

    // Test invalid_key
    lookup_result = ioopm_hash_table_lookup(ht, invalid_key);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    ioopm_hash_table_destroy(ht);
}

void test_lookup_empty() //TODO: check that it's actually working (not null/null)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    for (int i = 0; i < 18; ++i) /// 18 is a bit magical and should be changed depending on buckets
    {
        option_t *lookup_result = ioopm_hash_table_lookup(ht, i);
        CU_ASSERT_FALSE(lookup_result->success);
        free(lookup_result);
    }
    option_t *lookup_result = ioopm_hash_table_lookup(ht, -1);
    CU_ASSERT_FALSE(lookup_result->success);

    free(lookup_result);
    ioopm_hash_table_destroy(ht);
}

void test_remove_entry()
{
    // Write tests both for removing things you have inserted
    // and for (trying to) remove things you have not inserted.
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    int key1 = 1;
    int key2 = 18;
    int key3 = 35;
    int key4 = 52;
    ioopm_hash_table_insert(ht, key1, "value1");
    ioopm_hash_table_insert(ht, key2, "value2");
    ioopm_hash_table_insert(ht, key3, "value3");
    ioopm_hash_table_insert(ht, key4, "value4");

    // Remove inserted item (middle)
    char *value_removed = ioopm_hash_table_remove(ht, key2);
    CU_ASSERT_STRING_EQUAL("value2", value_removed);
    option_t *lookup_result = ioopm_hash_table_lookup(ht, key2);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    // Remove inserted item (last)
    value_removed = ioopm_hash_table_remove(ht, key4);
    lookup_result = ioopm_hash_table_lookup(ht, key4);
    CU_ASSERT_STRING_EQUAL("value4", value_removed);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    // Remove inserted item (first)
    value_removed = ioopm_hash_table_remove(ht, key1);
    lookup_result = ioopm_hash_table_lookup(ht, key1);
    CU_ASSERT_STRING_EQUAL("value1", value_removed);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    // Remove for not inserted item
    value_removed = ioopm_hash_table_remove(ht, key1);
    lookup_result = ioopm_hash_table_lookup(ht, key1);
    CU_ASSERT_STRING_EQUAL("key does not have an entry", value_removed);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    ioopm_hash_table_destroy(ht);
}

void test_size_hash_table()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(); 
    CU_ASSERT_EQUAL(17, ioopm_hash_table_size(ht)); 

    ioopm_hash_table_insert(ht, 1, "value1");
    ioopm_hash_table_insert(ht, 2, "value1");
    ioopm_hash_table_insert(ht, 18, "value1");

    CU_ASSERT_EQUAL(20, ioopm_hash_table_size(ht)); 

    ioopm_hash_table_clear(ht); 
    CU_ASSERT_EQUAL(17, ioopm_hash_table_size(ht)); 
    
    ioopm_hash_table_destroy(ht); 
}

void test_is_empty_hash_table() 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(); 
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht)); 

    ioopm_hash_table_insert(ht, 1, "value1");
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht)); 

    ioopm_hash_table_destroy(ht); 
}

void test_clear_hash_table() 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(); 
    ioopm_hash_table_insert(ht, 1, "value1");
    ioopm_hash_table_insert(ht, 2, "value2");
    ioopm_hash_table_insert(ht, 18, "value3");

    ioopm_hash_table_clear(ht); 
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht)); 

    option_t *lookup_result = ioopm_hash_table_lookup(ht, 18);
    CU_ASSERT_TRUE(Unsuccessful((*lookup_result)));
    free(lookup_result);

    CU_ASSERT_EQUAL(17, ioopm_hash_table_size(ht)); 

    ioopm_hash_table_destroy(ht); 
}

void test_table_keys()
{
    int keys_to_test[5] = {3, 10, 42, 0, 99}; 
    bool found[5] = {false}; 
        
    ioopm_hash_table_t *ht = ioopm_hash_table_create(); 
    for (int i = 0; i < 5; i++)
    {
        ioopm_hash_table_insert(ht, keys_to_test[i], "not important");
    }

    int *keys_from_ht = ioopm_hash_table_keys(ht);

    //Iterate over the reuslting array 
    for (int i = 0; i < 5; i++)
    {
        int key = keys_from_ht[i]; 

        //For each key, find the corresponding index of the key in keys and set that index to true in found.
        for (int j = 0; j < 5; j++)
        {
            if (keys_to_test[j] == key)
            {
                found[i] = true; 
            }
        }

        if (!found[i]) 
        {
            CU_FAIL("Found a key that was never inserted!"); 
        }
    } 

    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_TRUE(found[i]); 
    }

    free(keys_from_ht); 
    ioopm_hash_table_destroy(ht); 
}

void test_table_values()
{
    int keys_to_test[5] = {3, 10, 42, 0, 99}; 
    char *values_to_test[5] =  {"three", "ten", "fortytwo", "zero", "ninetynine"}; 
    bool found[5] = {false}; 
        
    ioopm_hash_table_t *ht = ioopm_hash_table_create(); 
    for (int i = 0; i < 5; i++)
    {
        ioopm_hash_table_insert(ht, keys_to_test[i], values_to_test[i]);
    }

    int *keys_from_ht = ioopm_hash_table_keys(ht);
    char **values_from_ht = ioopm_hash_table_values(ht);

    //Iterate over the reuslting array 
    for (int i = 0; i < 5; i++)
    {
        int key = keys_from_ht[i]; 
        char *value = values_from_ht[i]; 
        
        bool key_found = false;
        bool value_found = false;  

        for (int j = 0; j < 5; j++)
        {
            //For each key and value at the same index, separated for debugging
            if (keys_to_test[j] == key)
            {
                key_found = true; 

                if (values_to_test[j] == value) 
                {
                    value_found = true; 
                }
            }
        }

        if (!key_found) 
        {
            CU_FAIL("Found a key that was never inserted!"); 
        }
        else if (!value_found)
        {
            CU_FAIL("Value mismatch for key"); 
        }
        else 
        {
            found[i] = true; 
        }

    } 

    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_TRUE(found[i]); 
    }

    free(keys_from_ht); 
    free(values_from_ht); 
    ioopm_hash_table_destroy(ht); 
}

void test_ht_has_key()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    int key1 = 1;  
    int key2 = 18;
    int key3 = 35;  
    ioopm_hash_table_insert(ht, key1, "value1"); 
    ioopm_hash_table_insert(ht, key2, "value2"); 

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key2)); 
    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key3));

    ioopm_hash_table_destroy(ht); 
}

void test_ht_has_value() 
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    int key1 = 1;  
    int key2 = 18; 
    char *value1 = "value1"; 
    char *value2 = "value2";
    char *value3 = "value3";  
    ioopm_hash_table_insert(ht, key1, value1); 
    ioopm_hash_table_insert(ht, key2, value2); 

    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, value2)); 
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, value3)); 

    ioopm_hash_table_destroy(ht); 
}

static bool key_equiv(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key == other_key;
}

static bool value_equiv(int key_ignored, char *value, void *x)
{
  return strcmp(value, (char *)x) == 0;
}

void test_ht_has_any()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key1 = 1;  
    int key2 = 18; 
    int key3 = 27;
    int false_key = 17; 
    char *value1 = "value1"; 
    char *value2 = "value2";
    char *value3 = "value3"; 
    char *false_value = "no";
    ioopm_hash_table_insert(ht, key1, value1); 
    ioopm_hash_table_insert(ht, key2, value2); 
    ioopm_hash_table_insert(ht, key3, value3); 

    CU_ASSERT_TRUE(ioopm_hash_table_any(ht, key_equiv, &key2)); 
    CU_ASSERT_FALSE(ioopm_hash_table_any(ht, key_equiv, &false_key)); 

    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, value_equiv, value1))
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, value_equiv, false_value));

    ioopm_hash_table_destroy(ht); 
}

static bool mod_equiv(int key, char *value_ignored, void *x)
{
    // cast arg to int* and dereference it
    return key % *((int *)x) == 1;
}

static bool starts_with_char(int key, char *value, void *arg) {
    // cast arg to char and dereference it
    return value[0] == *((char *)arg);
}

void test_ht_has_all()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key1 = 1;  
    int key2 = 18; 
    int key3 = 35;
    int mod = 17; 
    char *value1 = "value1"; 
    char *value2 = "value2";
    char *value3 = "value3"; 
    char *false_value = "no";
    ioopm_hash_table_insert(ht, key1, value1); 
    ioopm_hash_table_insert(ht, key2, value2); 
    ioopm_hash_table_insert(ht, key3, value3); 

    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, mod_equiv, &mod)); 
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, mod_equiv, &false_value)); //false_value will be converted to int (ascii)

    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, starts_with_char, "v"))
    //CU_ASSERT_FALSE(ioopm_hash_table_all(ht, starts_with_char, limit)); //seg fault

    ioopm_hash_table_destroy(ht); 
}

static void add_version_value(int key_ignored, char **value, void *arg) {
    char *version = (char *)arg; 
    char *original_value = *value;

    // allocate memory for the new value, since new value has more characters than the original
    char *new_value = (char *)calloc(1, strlen(version) + strlen(original_value) + 1); // +1 for null-terminator

    strcpy(new_value, version);
    strcat(new_value, original_value);

    // Update the value in the hash table
    *value = new_value;
}


void test_ht_apply_to_all()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    char *version = "version 2: ";
    char *false_value = "no";

    int keys[3] = {1, 18, 27}; 
    char *values[3] =  {"value1", "value2", "value3"}; 
    bool found[3] = {false}; 
        
    for (int i = 0; i < 3; i++)
    {
        ioopm_hash_table_insert(ht, keys[i], values[i]);
    }

    ioopm_hash_table_apply_to_all(ht, add_version_value, version); //!!!!!!!!!!!!!!!!!!!

    char **array_apply_all = ioopm_hash_table_values(ht); 

    for (int i = 0; i < 3; i++)
    {
        char *value_after_apply = array_apply_all[i]; 
        bool value_updated = false;  

        for (int j = 0; j < 3; j++)
        {
            char *expected_value = strcat("version 2: ", values[j]); 
            if (!strcmp(value_after_apply, expected_value))
            // if (!strcmp(current->value, value) && !strcmp(duplicate, value) && current->value == value)
            {
                value_updated = true; 
            }
            
        }

        if (!value_updated)
        {
            CU_FAIL("Value not updated"); 
        }
        else 
        {
            found[i] = true; 
        }

    } 

    for (int i = 0; i < 5; i++)
    {
        CU_ASSERT_TRUE(found[i]); 
    }

    free(array_apply_all); 
    ioopm_hash_table_destroy(ht); 

}

int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        // If the test suite could not be added, tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    // This is where we add the test functions to our test suite.
    // For each call to CU_add_test we specify the test suite, the
    // name or description of the test, and the function that runs
    // the test in question. If you want to add another test, just
    // copy a line below and change the information
    if (
        (CU_add_test(my_test_suite, "A simple create and destroy test", test_create_destroy) == NULL ||
         CU_add_test(my_test_suite, "A simple insert and lookup test", test_insert_once) == NULL ||
         CU_add_test(my_test_suite, "Empty lookup", test_lookup_empty) == NULL ||
         CU_add_test(my_test_suite, "Remove a single element", test_remove_entry) == NULL ||
         CU_add_test(my_test_suite, "Test size of a hash_table", test_size_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Test for an empty hash table", test_is_empty_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Clearing a hash_table", test_clear_hash_table) == NULL ||
         CU_add_test(my_test_suite, "Test on a generated array of keys", test_table_keys) == NULL ||
         CU_add_test(my_test_suite, "Test on a generated array of values", test_table_values) == NULL ||
         CU_add_test(my_test_suite, "If hash table has key, with any test", test_ht_has_key) == NULL ||
         CU_add_test(my_test_suite, "Predicate function that satisfies any antry", test_ht_has_value) == NULL ||
         CU_add_test(my_test_suite, "Predicate function that satisfies all entries", test_ht_has_all) == NULL ||
         CU_add_test(my_test_suite, "Apply function on all entries", test_ht_apply_to_all) == NULL
        )
       )
    {
        // If adding any of the tests fails, we tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
    // Use CU_BRM_NORMAL to only print errors and a summary
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // This is where the tests are actually run!
    CU_basic_run_tests();

    // Tear down CUnit before exiting
    CU_cleanup_registry();
    return CU_get_error();
}
