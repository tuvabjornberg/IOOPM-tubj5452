#include <stdbool.h>

typedef struct list list_t;

/**
   @brief Create a new, empty list.
   @return a new, empty list
*/
list_t *list_create(void);

/**
   @brief Destroy a list, freeing all its allocated memory. Note that
   elements should not be free'd!
   @param l the list to be destroyed
*/
void list_destroy(list_t *l);

/**
   @brief Insert an element at a given index
   @param l the list to be inserted into
   @param s the element to be inserted
   @param index the index to be inserted at
   @return `true` if `index` was in the interval [0, length(l)], false otherwise
*/
bool list_insert(list_t *l, char *s, int index);

/**
   @brief Get the element at a given index and updates the latest position
   @param l the list to be indexed
   @param index the index to be accessed
   @return the element at index `index`, or `NULL` if the index was out of bounds
*/
char *list_get(list_t *l, int index);

/**
   @brief Insert an element at the latest position
   @param l the list to be inserted into
   @param s the element to be inserted
*/
void list_insert_at_latest(list_t *l, char *s);

/**
   @brief Remove and return the element at the latest position
   @param l the list to be removed from
   @return the removed element, or `NULL` if there are no more elements to remove from the latest position
*/
char *list_remove_at_latest(list_t *l);
