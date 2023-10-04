#pragma once

#include <stdbool.h>

#define BUF_SIZE 255

typedef union {
  int int_value;
  float float_value;
  char *string_value;
} answer_t;
typedef bool(*check_func)(char*);
typedef answer_t(*convert_func)(char*);

bool not_empty(char *str);
int read_string(char *buf, int buf_size);
answer_t ask_question(char *question, check_func check, convert_func convert);
int ask_question_int(char *question);
char *ask_question_string(char *question);
bool is_number(char *str);
