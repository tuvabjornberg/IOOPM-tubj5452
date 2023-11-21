#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct link link_t;

struct link {
  char *elem;
  link_t *next;
};

static link_t *link_create(char *elem, link_t *next) {
  link_t *link = calloc(1, sizeof(link_t));
  link->elem = elem;
  link->next = next;
  return link;
}

struct list {
  link_t *first;
  link_t *remembered_pointer; 
};

list_t *list_create(void) {
  list_t *list = calloc(1, sizeof(list_t));
  return list;
}

void list_destroy(list_t *l) {
  link_t *cursor = l->first;
  while (cursor) {
    link_t *next = cursor->next;
    free(cursor);
    cursor = next;
  }
  free(l);
}

bool list_insert(list_t *l, char *s, int index) {
  if (index == 0) {
    l->first = link_create(s, l->first);
    return true;
  }

  link_t *cursor = l->first;
  for (int i = 1; i < index; ++i){
    if (!cursor) {
      return false;
    }
    cursor = cursor->next;
  }

  if (!cursor) {
    return false;
  }

  cursor->next = link_create(s, cursor->next);
  return true;
}

char *list_get(list_t *l, int index) {
  if(index < 0) {
    return NULL;
  }

  link_t *cursor = l->first;
  link_t *prev = NULL;  

  for (int i = 0; i < index; ++i){
    if (!cursor) {
      return NULL;
    }
    prev = cursor; 
    cursor = cursor->next;
  }
  if (!cursor) {
    return NULL;
  }

  l->remembered_pointer = prev; 
  return cursor->elem;
}

void list_insert_at_latest(list_t *l, char *s) {
  link_t *prev = l->remembered_pointer; 
  if (prev == NULL)
  {
    list_insert(l, s, 0); 
  }
  else 
  {
    link_t *current = prev->next; 
    prev->next = link_create(s, current); 
  }
}

char *list_remove_at_latest(list_t *l) {
  link_t *prev = l->remembered_pointer; 

  if (l->first == NULL)
  {
    return NULL;
  }
  else if (prev == NULL)
  {
    link_t *first = l->first; 
    link_t *second = first->next; 

    char *removed_value =  first->elem;

    free(first); 
    l->first = second; 

    return removed_value; 
  }
  else if (prev->next == NULL)
  {
    return NULL; 
  }
  else
  {
    link_t *current = prev->next;
    link_t *next = current->next; 
    prev->next = next;
    
    char *removed_value = current->elem; 

    free(current); 

    return removed_value; 
  }
}

#ifndef TEST
int main(void)
{
  puts("If you want to you can write test code here and run it using `make run`");
  return 0;
}
#endif