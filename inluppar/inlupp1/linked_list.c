#include <stdlib.h>
#include "linked_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct link link_t;

struct link
{
    int value;
    struct link *next;
};
struct list
{
  link_t *first;
  link_t *last;
  size_t size;
};

ioopm_list_t *ioopm_linked_list_create() 
{
    return calloc(1, sizeof(struct list));
}

void ioopm_linked_list_destroy(ioopm_list_t *list) 
{
    link_t *current = list->first;
    while (current != NULL) {
        link_t *next = current->next;
        free(current);
        current = next;
    }
    free(list); 
}

static link_t *link_create(int value, link_t *next)
{
    link_t *new_link = calloc(1, sizeof(link_t)); 
    new_link->value = value;
    new_link->next = next; 
    return new_link; 
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    link_t *new_link = link_create(value, NULL); 

    if (new_link != NULL) { //check if mem was allocated correctly
        if (list->last == NULL) {
            // if empty list
            list->first = new_link;
        } else {
            // if non-empty list 
            list->last->next = new_link;
        }

        list->last = new_link;
        list->size++;
    }
}

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    link_t *new_link = link_create(value, list->first);

    if (new_link != NULL) //check if mem was allocated correctly
    {
        list->first = new_link; 
        if (list->last == NULL)
        {
            //if empty list
            list->last = new_link; 
        }
        list->size++; 
    }

}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    link_t *current = list->first; 
    int counter = 0; 
    int linked_list_size = ioopm_linked_list_size(list); 

    if (index == 0)
    {
        ioopm_linked_list_prepend(list, value); 
    }
    else if (index == linked_list_size)
    {
        ioopm_linked_list_append(list, value); 
    }
    else 
    {
        while (index > 0 && index < linked_list_size - 1 && counter <= index) 
        {
            if (counter == index - 1)
            {            
                link_t *new_link = link_create(value, NULL); 
                link_t *tmp = current->next; 
                current->next = new_link; 
                new_link->next = tmp; 
                list->size++; 
                //break; 
            }
            counter++; 
            current = current->next; 
        }
    }
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    link_t *current = list->first; 
    int counter = 0; 
    int linked_list_size = ioopm_linked_list_size(list);
    int value = 0;  

    if (list != NULL)
    {
        //first index
        if (index == 0)
        {
            value = list->first->value; 
            link_t *tmp = list->first->next; 
            free(list->first); 
            list->first = tmp; 
            list->size--; 
        }
        else 
        {
            while (index > 0 && index < linked_list_size  && counter < index) 
            {
                value = current->value; 
                //last index
                if (index == linked_list_size - 2 && current->next == NULL) 
                {
                    free(current->next); 
                    current->next = NULL;
                    list->last = current;  
                    list->size--; 
                }
                //middle index
                else if (counter == index - 1 ) //&& current->next- != NULL)
                {            
                    link_t *tmp = current->next->next; 
                    free(current->next); 
                    current->next = tmp;
                    list->size--;  
                }

                counter++; 
                current = current->next; 
            }
        }
    }
    return value; 
}

int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    link_t *current = list->first; 
    int counter = 0; 
    if (index >= 0 && index < ioopm_linked_list_size(list)) //if correct index input
    {
        while (counter != index)
        {
            current = current->next; 
            counter++; 
        }

        return current->value; 
    }
    else 
    {
        //invalid input
        return -1; 
    }
}


bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    link_t *current = list->first; 
    while (current != NULL)
    {
        if (current->value == element)
        {
            return true; 
        }
        current = current->next; 
    }
    return false; 
}


int ioopm_linked_list_size(ioopm_list_t *list)
{
    return list->size; 
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    return list->size == 0; 
}


void ioopm_linked_list_clear(ioopm_list_t *list)
{

}

