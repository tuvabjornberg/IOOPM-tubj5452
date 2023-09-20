#include <CUnit/Basic.h>
#include "linked_list.h"
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

void test_create_destroy() {
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_PTR_NOT_NULL(list);
    ioopm_linked_list_destroy(list);
}

void test_append()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
        CU_ASSERT_TRUE(ioopm_linked_list_contains(list, values[i]));
    }
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4); 
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, 5));

    ioopm_linked_list_destroy(list);
}

void test_prepend()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {1, 2, 3, 4}; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_prepend(list, values[i]); 
        CU_ASSERT_TRUE(ioopm_linked_list_contains(list, values[i]));
    }
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4); 
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, 5));

    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2), 2); 
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 1) == 3); 

    ioopm_linked_list_destroy(list);
}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {1, 2, 3, 4}; 
    int value_insert = 5; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }
    
    ioopm_linked_list_insert(list, 2, value_insert); 
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 5); 
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, value_insert));
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2), 5); 
    
    ioopm_linked_list_insert(list, 0, value_insert); 
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2) == 2);
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 0), 5); 
 
    ioopm_linked_list_insert(list, 6, value_insert); 
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 6) == 5); 
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 5), 4); 

    ioopm_linked_list_destroy(list);
}

void test_remove()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8}; 
    for (int i = 0; i < 8; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 8); 

    //remove first item
    int return_value = ioopm_linked_list_remove(list, 0); 
    int size = ioopm_linked_list_size(list); 
    CU_ASSERT_EQUAL(return_value, 1); 
    CU_ASSERT_EQUAL(size, 7);    
    for (int i = 0; i < size - 1; i++)
    {
      CU_ASSERT_EQUAL(ioopm_linked_list_get(list, i), i + 2);   
    }

    //remove last item
    return_value = ioopm_linked_list_remove(list, 6);
    size = ioopm_linked_list_size(list); 
    CU_ASSERT_EQUAL(return_value, 8); 
    CU_ASSERT_EQUAL(size, 6);     
    for (int i = 0; i < size - 1; i++)
    {
      CU_ASSERT_EQUAL(ioopm_linked_list_get(list, i), i + 2);   
    }

    //remove middle item
    return_value = ioopm_linked_list_remove(list, 2); 
    size = ioopm_linked_list_size(list); 
    CU_ASSERT_EQUAL(return_value, 4); 
    CU_ASSERT_EQUAL(size, 5);     
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2) == 5); 
    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 4), 7);  
    
    ioopm_linked_list_destroy(list);
}

void test_get()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {9, 8, 7, 6}; 
    int value_insert = 5; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }

    CU_ASSERT_EQUAL(ioopm_linked_list_get(list, 2), 7); 
    
    ioopm_linked_list_insert(list, 2, value_insert);    
    CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2) == 5);

    ioopm_linked_list_destroy(list); 
}


void test_contains()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {1, 2, 3, 4}; 
    int false_value = 5; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }
    
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, 3));   
    CU_ASSERT_EQUAL(ioopm_linked_list_contains(list, 3), true)  
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, false_value));

    ioopm_linked_list_destroy(list);
}


void test_size()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), NULL)  

    int values[4] = {1, 2, 3, 4}; 
    int value_insert = 5; 

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }
    
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 4) 

    //append
    ioopm_linked_list_append(list, value_insert); 
    CU_ASSERT_TRUE(ioopm_linked_list_size(list) == 5);

    //prepend
    ioopm_linked_list_prepend(list, value_insert); 
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 6);

    //insert
    ioopm_linked_list_insert(list, 3, value_insert); 
    CU_ASSERT_TRUE(ioopm_linked_list_size(list) == 7);

    ioopm_linked_list_destroy(list);
}

void test_is_empty()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list)); 

    int value_insert = 1; 
    ioopm_linked_list_append(list, value_insert); 
    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list)); 

    ioopm_linked_list_destroy(list);
}


void test_clear()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    int values[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++)
    {
        ioopm_linked_list_append(list, values[i]); 
    }

    ioopm_linked_list_clear(list);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));

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
         CU_add_test(my_test_suite, "Append element to linked list", test_append) == NULL ||
         CU_add_test(my_test_suite, "Prepend element to linked list", test_prepend) == NULL || 
         CU_add_test(my_test_suite, "Insert test", test_insert) == NULL ||
         CU_add_test(my_test_suite, "A simple contain element test", test_contains) == NULL ||
         CU_add_test(my_test_suite, "Test for linked list size", test_size) == NULL ||
         CU_add_test(my_test_suite, "Test if list is empty", test_is_empty) == NULL ||
         CU_add_test(my_test_suite, "Get value correctly", test_get) == NULL ||
         CU_add_test(my_test_suite, "Test for removing elements", test_remove) == NULL || 
         CU_add_test(my_test_suite, "Test for clearing list", test_clear) == NULL
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
