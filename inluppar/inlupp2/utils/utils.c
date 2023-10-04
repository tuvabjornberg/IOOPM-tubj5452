#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_number(char *str)
{
  int length = strlen(str);
  if (!(isdigit(str[0]) || str[0] == '-'))
    {
     return false; 
    }
  for (int i = 1; i < length; i++)
  {
    if (!isdigit(str[i])) return false;
  }
  return true;
}

int read_string(char *buf, int buf_size)
{
  if (!fgets(buf, buf_size, stdin))
    {
      return 0;
    }

  if (buf[strlen(buf) - 1] != '\n')
    {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
    }

  buf[strcspn(buf, "\n")] = '\0';
  
  return strlen(buf);
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
  char *answer = malloc(BUF_SIZE);
  
  puts(question);
  read_string(answer, BUF_SIZE);      

  while(!check(answer))
    {
      puts("Invalid input");
      read_string(answer, BUF_SIZE);
    }

  if (convert)
    {
      answer_t result = convert(answer);
      free(answer);
      return result;
    }
  return (answer_t){.string_value = answer};
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, NULL).string_value;
}

int ask_question_int(char *question)
{
  return ask_question(question, is_number, (convert_func)atoi).int_value;
}
