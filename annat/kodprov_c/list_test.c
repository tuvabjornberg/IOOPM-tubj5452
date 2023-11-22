#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "list.h"

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test_basic(void)
{
  list_t *l = list_create();
  CU_ASSERT_TRUE(list_insert(l, "a", 0));
  CU_ASSERT_TRUE(list_insert(l, "b", 1));
  CU_ASSERT_TRUE(list_insert(l, "c", 2));

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "b");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "c");

  CU_ASSERT_TRUE(list_insert(l, "aa", 0));
  CU_ASSERT_TRUE(list_insert(l, "bb", 2));
  CU_ASSERT_TRUE(list_insert(l, "cc", 4));

  CU_ASSERT_FALSE(list_insert(l, "bad index", 7));

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "aa");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "bb");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "b");
  CU_ASSERT_STRING_EQUAL(list_get(l, 4), "cc");
  CU_ASSERT_STRING_EQUAL(list_get(l, 5), "c");

  CU_ASSERT_PTR_NULL(list_get(l, 7));
  CU_ASSERT_PTR_NULL(list_get(l, -1));

  list_destroy(l);
}

void test_insert_at_latest(void) {
  list_t *l = list_create();
  list_insert(l, "a", 0);
  list_insert(l, "small", 1);
  list_insert(l, "dog", 2);

  // Latest position should be 0 (since get was not called yet)
  list_insert_at_latest(l, "pet");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "pet");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "small");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "dog");

  // Set the latest position to 2
  list_get(l, 2);
  list_insert_at_latest(l, "very");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "pet");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "very");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "small");
  CU_ASSERT_STRING_EQUAL(list_get(l, 4), "dog");

  // Set the latest position to 2
  list_get(l, 4);

  // An out-of-bounds get should not update the latest position
  list_get(l, -1);
  list_get(l, 5);

  list_insert_at_latest(l, "cute");
  list_insert_at_latest(l, "and");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "pet");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "very");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "small");
  CU_ASSERT_STRING_EQUAL(list_get(l, 4), "and");
  CU_ASSERT_STRING_EQUAL(list_get(l, 5), "cute");
  CU_ASSERT_STRING_EQUAL(list_get(l, 6), "dog");

  list_destroy(l);
}

void test_remove_at_latest(void) {
  list_t *l = list_create();
  list_insert(l, "don't", 0);
  list_insert(l, "eat", 1);
  list_insert(l, "broccoli", 2);

  // Latest position should be 0 (since get was not called yet)
  char *result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "don't");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "eat");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "broccoli");

  // Latest position is now 1 (because of the get above)
  result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "broccoli");

  // Latest position is now at the end of the list and remove should not work:
  CU_ASSERT_PTR_NULL(list_remove_at_latest(l));

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "eat");
  CU_ASSERT_PTR_NULL(list_get(l, 1));

  // Latest position is now 0 (because of the latest successful get above)
  result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "eat");

  // List is now empty
  CU_ASSERT_PTR_NULL(list_get(l, 0));
  CU_ASSERT_PTR_NULL(list_remove_at_latest(l));

  list_destroy(l);
}

void test_insert_and_remove(void) {
  list_t *l = list_create();
  list_insert_at_latest(l, "me");
  list_insert_at_latest(l, "remove");

  char *result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "remove");

  result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "me");

  list_insert_at_latest(l, "strings");
  list_insert_at_latest(l, "of");
  list_insert_at_latest(l, "bunch");
  list_insert_at_latest(l, "a");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "bunch");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "of");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "strings");

  // Latest position is now 3
  result = list_remove_at_latest(l);
  CU_ASSERT_STRING_EQUAL(result, "strings");

  // Latest position is now at the end of the list and remove should not work:
  CU_ASSERT_PTR_NULL(list_remove_at_latest(l));

  list_insert_at_latest(l, "fun!");

  CU_ASSERT_STRING_EQUAL(list_get(l, 0), "a");
  CU_ASSERT_STRING_EQUAL(list_get(l, 1), "bunch");
  CU_ASSERT_STRING_EQUAL(list_get(l, 2), "of");
  CU_ASSERT_STRING_EQUAL(list_get(l, 3), "fun!");

  list_destroy(l);
}

int main()
{
  CU_pSuite list_test_suite = NULL;
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  list_test_suite = CU_add_suite("List Test Suite", init_suite, clean_suite);
  if (NULL == list_test_suite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(list_test_suite, "Test basic functions", test_basic)) ||
    (NULL == CU_add_test(list_test_suite, "Test insertion at latest", test_insert_at_latest)) ||
    (NULL == CU_add_test(list_test_suite, "Test removal at latest", test_remove_at_latest)) ||
    (NULL == CU_add_test(list_test_suite, "Test both insert and remove", test_insert_and_remove)) ||
    false
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
