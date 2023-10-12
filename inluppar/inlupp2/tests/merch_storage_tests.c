#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../logic/merch_storage.h"
#include "../utils/utils.h"

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
/*
char *malloc_input()
{
    char *answer = calloc(1, sizeof(char *));  

}

merch_t *create_test_merch(store_t *store)
{
    char *name = calloc(1, sizeof(char*)); 
    name = "Apple";

    char *description = calloc(1, sizeof(char*)); 
    description = "Apple";
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 

}
*/
void create_destroy_merch_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_PTR_NOT_NULL(store); 
    store_destroy(store); 
}

void store_add_remove_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 

    store_add(store, apple); 
    CU_ASSERT_TRUE(merch_exists(store, name)); 
    CU_ASSERT_EQUAL(get_merch(store, name), apple); 

    store_remove(store, get_name(apple)); 
    CU_ASSERT_FALSE(merch_exists(store, name)); 
    CU_ASSERT_EQUAL(get_merch(store, name), NULL); 

    store_destroy(store); 
}

void stock_add_remove_test() 
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf[] = {"B36", "R62", "A4"}; 
    int quantity[] = {0, 1, 4}; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 

    for (int i = 0; i < 3; i++)
    {
        location_add(apple, strdup(shelf[i]), quantity[i]);
    }

    location_t *apple_location = get_location(apple, shelf[0]); 
    CU_ASSERT_EQUAL(get_quantity(apple_location), 0); 

    for (int i = 0; i < 3; i++)
    {
        apple_location = get_location(apple, shelf[i]);

        CU_ASSERT_EQUAL(apple_location->quantity, quantity[i]); 
        CU_ASSERT_STRING_EQUAL(apple_location->shelf, shelf[i]); 
    }

    location_add(apple, strdup(shelf[2]), 5); 
    apple_location = get_location(apple, shelf[2]);
    CU_ASSERT_EQUAL(apple_location->quantity, 9); 
    CU_ASSERT_STRING_EQUAL(apple_location->shelf, shelf[2]);

    location_add(apple, strdup(shelf[2]), -2);
    apple_location = get_location(apple, shelf[2]); 
    CU_ASSERT_EQUAL(apple_location->quantity, 7);

    store_destroy(store); 
}

void merch_exists_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_TRUE(store_is_empty(store)); 

    char *name = "Apple"; 
    char *non_input_name = "Pear"; 
    char *description = "Red"; 
    int price = 10; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    store_add(store, apple); 

    CU_ASSERT_TRUE(merch_exists(store, name)); 
    CU_ASSERT_FALSE(merch_exists(store, non_input_name)); 

    store_remove(store, name); 
    CU_ASSERT_FALSE(merch_exists(store, name)); 

    store_destroy(store); 
}

void store_size_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_EQUAL(store_size(store), 0); 
    
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 
    CU_ASSERT_EQUAL(store_size(store), 1); 

    store_remove(store, get_name(apple)); 
    CU_ASSERT_EQUAL(store_size(store), 0); 

    store_destroy(store);  
}

void get_merch_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *non_input_name = "Pear"; 
    char *description = "Red"; 
    int price = 10; 
     
    char *shelf[] = {"A36", "B62", "C4"}; 
    int quantity[] = {0, 1, 4}; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 

    for (int i = 0; i < 3; i++)
    {
        location_add(apple, strdup(shelf[i]), quantity[i]);
    }

    merch_t *apple_from_store = get_merch(store, name);
    CU_ASSERT_TRUE(!strcmp(apple->description, "Red"));
    CU_ASSERT_EQUAL(apple->price, 10);
    CU_ASSERT_STRING_EQUAL(get_description(apple_from_store), "Red");
    CU_ASSERT_EQUAL(get_price(apple_from_store), 10);

    merch_t *pear_from_store = get_merch(store, non_input_name);
    CU_ASSERT_PTR_NULL(pear_from_store);
    
    for (int i = 0; i < stock_size(apple_from_store); i++)
    {
        location_t *location = get_location(apple, shelf[i]); 
        CU_ASSERT_STRING_EQUAL(get_shelf(location), shelf[i]); 
        CU_ASSERT_EQUAL(get_quantity(location), quantity[i])
    }

    store_destroy(store); 
}

void set_name_test()
{
    store_t *store = store_create(string_sum_hash, string_eq);

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf[] = {"B36", "R62", "A4"}; 
    int quantity[] = {0, 1, 4}; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 

    for (int i = 0; i < 3; i++)
    {
        location_add(apple, strdup(shelf[i]), quantity[i]);
    }

    char *new_name = "Pear"; 
    set_name(store, apple, strdup(new_name)); 
    CU_ASSERT_TRUE(merch_exists(store, new_name)); 

    merch_t *updated_merch = get_merch(store, new_name); 
    CU_ASSERT_STRING_EQUAL(get_name(updated_merch), new_name); 
    CU_ASSERT_STRING_EQUAL(get_description(updated_merch), description); 
    CU_ASSERT_EQUAL(get_price(updated_merch), 10);
    
    set_description(updated_merch, strdup("Green")); 
    CU_ASSERT_STRING_NOT_EQUAL(get_description(updated_merch), description); 
    CU_ASSERT_STRING_EQUAL(get_description(updated_merch), "Green");  
    
    location_t *first_shelf = get_location(updated_merch, shelf[0]);
    CU_ASSERT_TRUE(!strcmp(get_shelf(first_shelf), "B36")); 
    CU_ASSERT_EQUAL(get_quantity(first_shelf), 0); 

    location_t *second_shelf = get_location(updated_merch, shelf[1]);
    CU_ASSERT_TRUE(!strcmp(get_shelf(second_shelf), "R62")); 
    CU_ASSERT_EQUAL(get_quantity(second_shelf), 1); 

    location_t *third_shelf = get_location(updated_merch, shelf[2]);
    CU_ASSERT_TRUE(!strcmp(get_shelf(third_shelf), "A4")); 
    CU_ASSERT_EQUAL(get_quantity(third_shelf), 4); 

    store_destroy(store); 
}

void set_description_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    
    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 

    set_description(apple, strdup("Green")); 
    CU_ASSERT_STRING_NOT_EQUAL(get_description(apple), description); 
    CU_ASSERT_STRING_EQUAL(get_description(apple), "Green"); 

    store_destroy(store); 
}

void set_price_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    
    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    store_add(store, apple); 

    set_price(apple, 30); 
    CU_ASSERT_NOT_EQUAL(get_price(apple), 10); 
    CU_ASSERT_EQUAL(get_price(apple), 30); 

    store_destroy(store); 
}

void store_is_empty_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_TRUE(store_is_empty(store)); 
    store_destroy(store); 
}

void stock_size_test() 
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf[] = {"B36", "R62", "A4"}; 
    int quantity[] = {0, 1, 4}; 

    merch_t *apple = merch_create(strdup(name), strdup(description), price, ioopm_linked_list_create(string_eq)); 
 
    
    CU_ASSERT_EQUAL(stock_size(apple), 0); 

    store_add(store, apple); 

    for (int i = 0; i < 3; i++)
    {
        location_add(apple, strdup(shelf[i]), quantity[i]);
        CU_ASSERT_EQUAL(stock_size(apple), i + 1); 
    }

    CU_ASSERT_TRUE(stock_size(apple) == 3); 

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
         CU_add_test(my_test_suite, "testing for adding and removing from store", store_add_remove_test) == NULL ||
         CU_add_test(my_test_suite, "test for adding and removing from stock", stock_add_remove_test) == NULL ||
         CU_add_test(my_test_suite, "test for merch existing", merch_exists_test) == NULL ||
         CU_add_test(my_test_suite, "test for the store size", store_size_test) == NULL ||
         CU_add_test(my_test_suite, "getting merch from store", get_merch_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing name of merch", set_name_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing description of merch", set_description_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing price of merch", set_price_test) == NULL ||
         CU_add_test(my_test_suite, "test if store is empty", store_is_empty_test) == NULL ||
         CU_add_test(my_test_suite, "test for a merch's stock", stock_size_test) == NULL 

         
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
