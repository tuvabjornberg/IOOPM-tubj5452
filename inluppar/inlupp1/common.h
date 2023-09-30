#pragma once
#include <stdbool.h>

#define int_elem(x) (elem_t) { .integer=(x) }
#define str_elem(x) (elem_t) { .string=(x) }

/**
 * @file common.h
 * @author Tuva Björnberg & Gustav Fridén
 * @date 11/09-2023
 * @brief 
 *
 *
 */

typedef union elem elem_t;

union elem
{
  int integer;
  unsigned int unsigned_integer;
  bool boolean;
  float float_number;
  char *string;
  void *void_ptr;
};

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

typedef unsigned int(*ioopm_hash_function)(elem_t key);