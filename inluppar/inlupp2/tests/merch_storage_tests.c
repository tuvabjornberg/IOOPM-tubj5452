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
    char *shelf = "A36"; 

    merch_t *apple = merch_create(name, description, price, shelf); 

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
    char *non_input_name = "Pear"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf = "A36"; 

    merch_t *apple = merch_create(name, description, price, shelf); 
    store_add(store, apple); 

    CU_ASSERT_EQUAL(get_stock(store, name), 0); 
    CU_ASSERT_EQUAL(get_stock(store, non_input_name), NULL); 

    stock_add(apple, 3); //TODO: replenish should do it??
    CU_ASSERT_EQUAL(get_stock(store, name), 4); 

    stock_add(apple, -2); //TODO: do we have stock add negative for remove (stock_add_remove) or seperate function (stock_add + stock_remove)
    CU_ASSERT_EQUAL(get_stock(store, name), 2); 

    store_destroy(store); 
}

void location_add_remove_test()
{
    store_t *store = store_create(string_sum_hash, string_eq);
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf = "A36"; 
    char *second_shelf = "B81"; 

    merch_t *apple = merch_create(name, description, price, shelf); 
    store_add(store, apple); 

    location_add(apple, second_shelf); 
    CU_ASSERT_TRUE(shelf_exists(apple, second_shelf))

    location_remove(apple, second_shelf); 
    CU_ASSERT_FALSE(shelf_exists(apple, second_shelf))

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
    char *shelf = "A36"; 

    merch_t *apple = merch_create(name, description, price, shelf); 
    store_add(store, apple); 

    CU_ASSERT_TRUE(merch_exists(store, name)); 
    CU_ASSERT_FALSE(merch_exists(store, non_input_name)); 

    store_destroy(store); 
}

void store_size_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_EQUAL(store_size(store), 0); 
    
    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf = "A36"; 

    merch_t *apple = merch_create(name, description, price, shelf); 
    
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

    merch_t *apple = merch_create(name, description, price, shelf[0]); 
    
    store_add(store, apple); 
    location_add(apple, shelf[1]);
    location_add(apple, shelf[2]);  

    //TODO: commented out will crash because get_merch is null (nothing to point to)
    merch_t *apple_from_store = get_merch(store, name);
    CU_ASSERT_EQUAL(apple->description, "Red");
    CU_ASSERT_EQUAL(apple->price, 10);
    //CU_ASSERT_EQUAL(apple_from_store->locations)
    CU_ASSERT_EQUAL(get_description(apple_from_store), "Red");
    CU_ASSERT_EQUAL(get_price(apple_from_store), 10);

    merch_t *pear_from_store = get_merch(store, non_input_name);
    CU_ASSERT_PTR_NOT_NULL(pear_from_store);
    
    //for (int i = 0; i < locations_size(apple_from_store); i++)
    //{
    //    char *shelf_from_list = get_shelf(store, get_name(apple_from_store), i);
    //    CU_ASSERT_TRUE(shelf_from_list == shelf[i]); 
    //    //CU_ASSERT_PTR_NOT_NULL(get_shelf(store, get_name(pear_from_store), i));
    //}

    store_destroy(store); 
}

void get_names_in_arr_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void get_stock_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_name_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_description_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void set_price_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    store_destroy(store); 
}

void store_is_empty_test()
{
    store_t *store = store_create(string_sum_hash, string_eq); 
    CU_ASSERT_TRUE(store_is_empty(store)); 
    store_destroy(store); 
}

void locations_size_test() //TODO: commented out in main because incomplete
{
    store_t *store = store_create(string_sum_hash, string_eq); 

    char *name = "Apple"; 
    char *description = "Red"; 
    int price = 10; 
    char *shelf[] = {"A36", "B62", "C4"}; 

    merch_t *apple = merch_create(name, description, price, shelf[0]); 
    
    store_add(store, apple); 
    location_add(apple, shelf[1]);
    location_add(apple, shelf[2]);  

    //CU_ASSERT_TRUE(locations_size(apple) == 3); 

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
         CU_add_test(my_test_suite, "test for adding to location", location_add_remove_test) == NULL ||
         CU_add_test(my_test_suite, "test for merch existing", merch_exists_test) == NULL ||
         CU_add_test(my_test_suite, "test for the store size", store_size_test) == NULL ||
         CU_add_test(my_test_suite, "getting merch from store", get_merch_test) == NULL ||
         CU_add_test(my_test_suite, "getting names of merch in an array", get_names_in_arr_test) == NULL ||
         CU_add_test(my_test_suite, "test for getting stock from merch", get_stock_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing name of merch", set_name_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing description of merch", set_description_test) == NULL ||
         CU_add_test(my_test_suite, "test for editing price of merch", set_price_test) == NULL ||
         CU_add_test(my_test_suite, "test if store is empty", store_is_empty_test) == NULL 
         //CU_add_test(my_test_suite, "test for a merch's locations", locations_size_test) == NULL 

         
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
