#include <stdlib.h>
#include "linked_list.h"
#include "iterator.h"
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

struct iter
{
    link_t *current; 
    ioopm_list_t *list; 
}; 

ioopm_list_t *ioopm_linked_list_create() 
{
    return calloc(1, sizeof(struct list));
}

void ioopm_linked_list_destroy(ioopm_list_t *list) 
{
    if (!ioopm_linked_list_is_empty(list))
    {
        ioopm_linked_list_clear(list); 
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

    if (new_link != NULL) //check if mem was allocated correctly
    { 
        if (list->last == NULL) 
        {
            // if empty list
            list->first = new_link;
        } 
        else 
        {
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
    int value = -1;  

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
                //last index
                if (index == linked_list_size - 2 && current->next == NULL) 
                {
                    value = current->value; 
                    free(current->next); 
                    current->next = NULL;
                    list->last = current;  
                    list->size--; 
                }

                //middle index
                else if (counter == index - 1) 
                {      
                    value = current->next->value;       
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
    link_t *current = list->first; 

    while (current != NULL) 
    {
        link_t *next = current->next;
        free(current);
        current = next;
        list->size--;
    }
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra) 
{
    link_t *current = list->first;
    
    while (current != NULL) 
    {
        if (!prop(current->value, extra)) 
        {
            return false;
        }

        current = current->next;
    }

    return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra) 
{
    link_t *current = list->first;
    
    while (current != NULL) 
    {
        if (prop(current->value, extra)) 
        {
            return true;
        }

        current = current->next;
    }
    
    return false;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra) 
{
    link_t *current = list->first;

    while (current != NULL) 
    {
        fun(&(current->value), extra);
        current = current->next;
    }
}

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list) 
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));

    if (iter == NULL) {
        return NULL;
    }

    iter->list = list;
    iter->current = list->first; 

    return iter;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) 
{
    return iter->current != NULL;
}

int ioopm_iterator_next(ioopm_list_iterator_t *iter) 
{
    if (!ioopm_iterator_has_next(iter)) {
        return 0; 
    }

    iter->current = iter->current->next; 
    return iter->current->value;
}

/*
int ioopm_iterator_remove(ioopm_list_iterator_t *iter)
{
    
}
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
    
}
*/

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    if (iter->current != NULL) 
    {
        iter->current = iter->list->first; 
    }
    else
    {
        iter->list->first = NULL; 
    }
}

int ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    if (iter->current != NULL)
    {
        return iter->current->value; 
    }
    else
    {
        return 0; 
    }
}
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter); 
}