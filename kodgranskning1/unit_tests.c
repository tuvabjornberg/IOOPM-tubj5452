
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "hash_table.h"
#include "iterators.h"
#include "linked_list.h"

#define No_Buckets 17


void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL, NULL, NULL);
   CU_ASSERT_PTR_NOT_NULL(ht);

   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t key = int_elem(3);
  elem_t *value = create_elem_t_string("ett");
  ioopm_hash_table_insert(ht, key, *value);

  elem_t *find = ioopm_hash_table_lookup(ht, key);
  
  CU_ASSERT_TRUE(strcmp(find->string, value->string) == 0);

 
  free(value);
  ioopm_hash_table_destroy(ht);

}

void test_insert_existing_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t key = int_elem(3);
  elem_t *value = create_elem_t_string("ett");
  elem_t *value2 = create_elem_t_string("två");

  ioopm_hash_table_insert(ht, key, *value);

  elem_t *find = ioopm_hash_table_lookup(ht, key);
  
  CU_ASSERT_TRUE(strcmp(find->string, value->string) == 0);

  ioopm_hash_table_insert(ht, key, *value2);
  
  CU_ASSERT_STRING_EQUAL(ioopm_hash_table_lookup(ht, key)->string, "två");

  free(value);
  free(value2);
  ioopm_hash_table_destroy(ht);

}

void test_lookup()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(3);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);

  elem_t *string = create_elem_t_string("test");
  
  ioopm_hash_table_insert(ht, num1, *string);
  ioopm_hash_table_insert(ht, num2, *string);
  ioopm_hash_table_insert(ht, num3, *string);

  elem_t *find = ioopm_hash_table_lookup(ht, num2);
  
  CU_ASSERT_TRUE(strcmp(find->string, "test") == 0);
  
  free(string);
  ioopm_hash_table_destroy(ht);


}

void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
   elem_t iter = int_elem(0);

   for (int i = 0; i < No_Buckets; ++i) 
     {
      iter.integer = i; 
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, iter));
     }
 
   ioopm_hash_table_destroy(ht);
}

void test_remove_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(4);
  elem_t *value = create_elem_t_string("Hello");
  
  ioopm_hash_table_insert(ht, num1, *value);
  
  elem_t *lookup = ioopm_hash_table_lookup(ht, num1);
  CU_ASSERT_STRING_EQUAL(lookup->string, "Hello");
  

  ioopm_hash_table_remove(ht, num1);
 
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, num1));

  free(value);
  ioopm_hash_table_destroy(ht);
  
}

void test_hash_table_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t num4 = int_elem(4);

  elem_t *value = create_elem_t_string("test");
  

  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  ioopm_hash_table_insert(ht, num1, *value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_insert(ht, num4, *value);
  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 4);

  ioopm_hash_table_remove(ht, num1);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);

  
  free(value);
  ioopm_hash_table_destroy(ht);
}

void test_empty_hash_table()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t *value = create_elem_t_string("test");
  elem_t num4 = int_elem(3);
  

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_insert(ht, num1, *value);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);
  ioopm_hash_table_insert(ht, num4, *value);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));


  free(value);
  ioopm_hash_table_destroy(ht);
}

void test_clear_hash_table()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t *value = create_elem_t_string("test");
  elem_t num4 = int_elem(3);
  
  ioopm_hash_table_insert(ht, num4, *value);
  ioopm_hash_table_insert(ht, num1, *value);
  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);

  ioopm_hash_table_clear(ht);

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  free(value);
  ioopm_hash_table_destroy(ht);

}

void test_get_all_hash_table_keys()
{
  int keys[5] = {3, 5, 8, 1, 4};
  bool found[5] = {false};
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t *value = create_elem_t_string("test");
  elem_t num4 = int_elem(3);
  elem_t num5 = int_elem(4); 

  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  ioopm_hash_table_insert(ht, num1, *value);
  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);
  ioopm_hash_table_insert(ht, num4, *value);
  ioopm_hash_table_insert(ht, num5, *value);

  ioopm_list_t *all_keys = ioopm_hash_table_keys(ht); 
  
  
  int key_not_in_original = 0;
  for (int i = 0; i < 5; i++) 
  {
    elem_t nyckel = ioopm_linked_list_get(all_keys, i);
    for (int j = 0; j < 5; j++) {
      if(keys[j] == nyckel.integer) {
        found[j] = true;
        key_not_in_original = 1;
        break;

      } 
    }
  }

  
  if(key_not_in_original == 0) { 
    CU_FAIL("Found a key that was never inserted!"); 
  }

  for (int i = 0; i < 5; i++) 
  {
    CU_ASSERT_TRUE(found[i]);
  }

  free(value);
  ioopm_linked_list_destroy(all_keys);
  ioopm_hash_table_destroy(ht);

}



void test_get_all_hash_table_values()
{
  char *values[5] = {"ett", "två", "tre", "fyra", "fem"};
  bool found[5] = {false};
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t num4 = int_elem(3);
  elem_t num5 = int_elem(4); 
  elem_t *value1 = create_elem_t_string("ett");
  elem_t *value2 = create_elem_t_string("två");
  elem_t *value3 = create_elem_t_string("tre");
  elem_t *value4 = create_elem_t_string("fyra");
  elem_t *value5 = create_elem_t_string("fem"); 



  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  ioopm_hash_table_insert(ht, num1, *value1);
  ioopm_hash_table_insert(ht, num2, *value2);
  ioopm_hash_table_insert(ht, num3, *value3);
  ioopm_hash_table_insert(ht, num4, *value4);
  ioopm_hash_table_insert(ht, num5, *value5);

  ioopm_list_t *all_values = ioopm_hash_table_values(ht);
  int value_not_in_original = 0;
  for (int i = 0; i < 5; i++) 
  {
    elem_t värde = ioopm_linked_list_get(all_values, i);
    for (int j = 0; j < 5; j++) {
      if(strcmp(values[j],värde.string) == 0) {
        found[j] = true;
        value_not_in_original = 1;
        break;

      } 
    }
  }

  if(value_not_in_original == 0) { 
    CU_FAIL("Found a value that was never inserted!"); 
  }
  for (int i = 0; i < 5; i++) 
  {
    CU_ASSERT_TRUE(found[i]);
  }
  free(value1);
  free(value2);
  free(value3);
  free(value4);
  free(value5);
  ioopm_linked_list_destroy(all_values);
  ioopm_hash_table_destroy(ht);

}

void test_get_all_keys_values()
{
  int keys[5] = {5, 8, 1, 3, 4};
  char *values[5] = {"ett", "två", "tre", "fyra", "fem"};
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t num4 = int_elem(3);
  elem_t num5 = int_elem(4); 
  elem_t *value1 = create_elem_t_string("ett");
  elem_t *value2 = create_elem_t_string("två");
  elem_t *value3 = create_elem_t_string("tre");
  elem_t *value4 = create_elem_t_string("fyra");
  elem_t *value5 = create_elem_t_string("fem"); 

  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  ioopm_hash_table_insert(ht, num1, *value1);
  ioopm_hash_table_insert(ht, num2, *value2);
  ioopm_hash_table_insert(ht, num3, *value3);
  ioopm_hash_table_insert(ht, num4, *value4);
  ioopm_hash_table_insert(ht, num5, *value5);

  ioopm_list_t *all_keys = ioopm_hash_table_keys(ht);
  ioopm_list_t *all_values = ioopm_hash_table_values(ht);
  int key_not_in_original = 0;

  for (int i = 0; i < 5; i++) 
  {
    elem_t key = ioopm_linked_list_get(all_keys, i);
    elem_t value = ioopm_linked_list_get(all_values, i);
    for (int j = 0; j < 5; j++) 
    {
      if (keys[j] == key.integer) 
      {
        key_not_in_original = 1;
        CU_ASSERT_TRUE(strcmp(value.string, values[j]) == 0);
        break;
      }
    }
    if (key_not_in_original == 0) 
    {
      CU_FAIL("Found a key that was never inserted!");
    }
  }

  free(value1);
  free(value2);
  free(value3);
  free(value4);
  free(value5);
  ioopm_linked_list_destroy(all_values);
  ioopm_linked_list_destroy(all_keys);
  ioopm_hash_table_destroy(ht);
}

void test_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t *value = create_elem_t_string("test");
  elem_t num4 = int_elem(3);
  elem_t num5 = int_elem(4);


  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, num3));

  ioopm_hash_table_insert(ht, num1, *value);
  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);
  ioopm_hash_table_insert(ht, num4, *value);
  ioopm_hash_table_insert(ht, num5, *value);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, num3));


  free(value);
  ioopm_hash_table_destroy(ht);

}

void test_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(5);
  elem_t num2 = int_elem(8);
  elem_t num3 = int_elem(1);
  elem_t num4 = int_elem(3);
  elem_t num5 = int_elem(4);
 
  
  elem_t *value1 = create_elem_t_string("ett");
  elem_t *value2 = create_elem_t_string("två");
  elem_t *value3 = create_elem_t_string("tre");
  elem_t *value4 = create_elem_t_string("fyra");
  elem_t *value5 = create_elem_t_string("fem"); 
  

  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, value4));

  ioopm_hash_table_insert(ht, num1, *value1);
  ioopm_hash_table_insert(ht, num2, *value2);
  ioopm_hash_table_insert(ht, num3, *value3);
  ioopm_hash_table_insert(ht, num4, *value4);
  ioopm_hash_table_insert(ht, num5, *value5);

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, value4));

  char *copy = strdup("tre");
  elem_t *copy_of_string = create_elem_t_string(copy);
  
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_of_string));

  free(copy);
  free(copy_of_string);
  free(value1);
  free(value2);
  free(value3);
  free(value4);
  free(value5);
  
  ioopm_hash_table_destroy(ht);

}

static bool pred(elem_t key, elem_t value, void *arg) {
  int divide = *((int *)arg);

  if(key.integer % divide == 0 && strcmp(value.string, "same") == 0) {
    return true;
  } else {
    return false;
  }

}
void test_hash_table_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(2);
  elem_t num2 = int_elem(4);
  elem_t num3 = int_elem(6);
  elem_t *value = create_elem_t_string("same");
  

  ioopm_hash_table_insert(ht, num1, *value);
  ioopm_hash_table_insert(ht, num2, *value);
  ioopm_hash_table_insert(ht, num3, *value);

  int divided = 2;
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, pred, &divided));

  free(value);
  ioopm_hash_table_destroy(ht);

  

}

void change_char(elem_t key_ignored, elem_t *value, void *arg) 
{
  value->string = "new_char";
}

static bool pred2(elem_t key_ignored, elem_t value, void *arg) {
  

  if(strcmp(value.string, "new_char") == 0) {
    return true;
  } else {
    return false;
  }

}

void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);
  elem_t num1 = int_elem(2);
  elem_t num2 = int_elem(10);
  elem_t num3 = int_elem(42);
  elem_t *value1 = create_elem_t_string("old_char");
  
  ioopm_hash_table_insert(ht, num1, *value1);
  ioopm_hash_table_insert(ht, num2, *value1);
  ioopm_hash_table_insert(ht, num3, *value1);


  ioopm_hash_table_apply_to_all(ht, change_char, NULL);
  
  CU_ASSERT(ioopm_hash_table_all(ht, pred2, NULL));

  free(value1);
 

  ioopm_hash_table_destroy(ht);

}

void test_value_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ht_func_int, compare_ints, eq_int_elements, eq_string_elements);

  elem_t num1 = int_elem(2);
  elem_t num2 = int_elem(10);
  elem_t num3 = int_elem(42);

  elem_t *value1 = create_elem_t_string("hell");
  elem_t *value2 = create_elem_t_string("hellddd");
  elem_t *value3 = create_elem_t_string("hellddddd");

  
  
  ioopm_hash_table_insert(ht, *value1, num1);
  ioopm_hash_table_insert(ht, *value2, num2);
  ioopm_hash_table_insert(ht, *value3, num3);


  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, *value1)->integer, 2);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, *value2)->integer, 10);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, *value3)->integer, 42);
 

  free(value1);
  free(value2);
  free(value3);
  ioopm_hash_table_destroy(ht);

}





int main() {
 
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  
  CU_pSuite my_test_suite = CU_add_suite("Hash table tests", NULL, NULL);
  

  if (
    (CU_add_test(my_test_suite, "Create destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Insert once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Insert already existing value", test_insert_existing_value) == NULL) ||
    (CU_add_test(my_test_suite, "Remove once", test_remove_once) == NULL) ||
    (CU_add_test(my_test_suite, "Size", test_hash_table_size) == NULL) ||
    (CU_add_test(my_test_suite, "Test if lookup returns right value", test_lookup) == NULL) ||
    (CU_add_test(my_test_suite, "Test if hash table is empty", test_empty_hash_table) == NULL) ||
    (CU_add_test(my_test_suite, "Clear a hash table", test_clear_hash_table) == NULL) ||
    (CU_add_test(my_test_suite, "Get all keys", test_get_all_hash_table_keys) == NULL) ||
    (CU_add_test(my_test_suite, "Get all values", test_get_all_hash_table_values) == NULL) ||
    (CU_add_test(my_test_suite, "Get all values and keys", test_get_all_keys_values) == NULL) ||
    (CU_add_test(my_test_suite, "Find if key in hash table", test_has_key) == NULL) ||
    (CU_add_test(my_test_suite, "Find if value in hash table", test_has_value) == NULL) ||
    (CU_add_test(my_test_suite, "predicate function on all elements", test_hash_table_all) == NULL) ||
    (CU_add_test(my_test_suite, "apply function on all elements", test_apply_to_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test values as keys and int as elements", test_value_keys) == NULL) ||
    0
  )
    {
     
      CU_cleanup_registry();
      return CU_get_error();
    }
 
  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();


  CU_cleanup_registry();
  return CU_get_error();
} 





