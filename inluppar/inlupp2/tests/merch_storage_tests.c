#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../logic/merch_storage.h"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

bool string_eq(elem_t e1, elem_t e2)
{
    return (strcmp(e1.string, e2.string) == 0);
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

void create_destroy_merch_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_PTR_NOT_NULL(store); 

    store_destroy(store); 
}

void store_add_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf = "A36"; 

    merch_t *apple = merch_create(name, description, price, shelf); 
    store_add(store, apple); 

    CU_ASSERT_TRUE(merch_exists(store, name)); 
    CU_ASSERT_EQUAL(get_merch(store, name), apple); 
    
    merch_destroy(apple);  
    store_destroy(store); 
}


void stock_add_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 

    store_destroy(store); 
}

void location_add_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void store_remove_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
} 

void merch_exists_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_TRUE(store_is_empty(store)); 

    store_destroy(store); 
}

void store_size_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_EQUAL(store_size(store), 0); 

    store_destroy(store);  
}

void get_merch_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void get_names_in_arr_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void get_stock_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_name_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_description_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_price_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void store_is_empty_test()
{
    ioopm_hash_table_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_TRUE(store_is_empty(store)); 
    store_destroy(store); 
}



int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("Tests for merch_storage.c", init_suite, clean_suite);
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
        (CU_add_test(my_test_suite, "simple create destroy merch test", create_destroy_merch_test) == NULL ||
         CU_add_test(my_test_suite, "testing for adding to store", store_add_test) == NULL ||
         CU_add_test(my_test_suite, "test for adding to location", location_add_test) == NULL ||
         CU_add_test(my_test_suite, "test for removing merch from store", store_remove_test) == NULL ||
         CU_add_test(my_test_suite, "test for merch existing", merch_exists_test) == NULL ||
         CU_add_test(my_test_suite, "test for the store size", store_size_test) == NULL ||
         CU_add_test(my_test_suite, "getting merch from store", get_merch_test) == NULL ||
         CU_add_test(my_test_suite, "getting names of merch in an array", get_names_in_arr_test) == NULL ||
         CU_add_test(my_test_suite, "test for getting stock from merch", get_stock_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing name of merch", set_name_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing description of merch", set_description_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing price of merch", set_price_test) == NULL ||
         CU_add_test(my_test_suite, "test if store is empty", store_is_empty_test) == NULL 
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
