#include <stdlib.h>
#include "linked_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct link 
{
    void *value;
    ioopm_link_t *next;
};

struct list
{
    ioopm_link_t *first;
    ioopm_link_t *last;  
};

ioopm_list_t *ioopm_linked_list_create() {
    return NULL;
}


void ioopm_linked_list_destroy(ioopm_list_t *list) {

}

