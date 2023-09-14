#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void) {
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}

int clean_suite(void) {
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
    int key2 = 2; 
    int key3 = 3; 

    ioopm_hash_table_insert(ht, key1, "value1");
    ioopm_hash_table_insert(ht, key2, "value2");
    ioopm_hash_table_insert(ht, key3, "value3");


    // Test key1
    option_t *result = ioopm_hash_table_lookup(ht, key1);

    CU_ASSERT_TRUE(Successful((*result)));
    CU_ASSERT_STRING_EQUAL("value1", result->value);
    ioopm_destroy_option(result); 


    // Test existing key
    result = ioopm_hash_table_lookup(ht, key2);
    CU_ASSERT_TRUE(Successful((*result)));
    CU_ASSERT_STRING_EQUAL("value2", result->value);
    ioopm_destroy_option(result); 

    // Test invalid_key
    result = ioopm_hash_table_lookup(ht, invalid_key);
    CU_ASSERT_FALSE(Unsuccessful((*result)));
    ioopm_destroy_option(result); 

    ioopm_hash_table_destroy(ht);
}

void test_lookup_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    for (int i = 0; i < 18; ++i) /// 18 is a bit magical and should be changed depending on buckets
    {
        option_t *result = ioopm_hash_table_lookup(ht, i); 
        CU_ASSERT_PTR_NULL(result);
        ioopm_destroy_option(result); 
    }
    option_t *result = ioopm_hash_table_lookup(ht, -1); 
    CU_ASSERT_PTR_NULL(result);

    ioopm_destroy_option(result); 
    ioopm_hash_table_destroy(ht);
}

int main() {
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
    if (my_test_suite == NULL) {
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
        (CU_add_test(my_test_suite, "A simple create_destroy test", test_create_destroy) == NULL ||
        CU_add_test(my_test_suite, "A simple insert_lookup test", test_insert_once) == NULL ||
	    CU_add_test(my_test_suite, "Empty lookup", test_lookup_empty) == NULL)
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
