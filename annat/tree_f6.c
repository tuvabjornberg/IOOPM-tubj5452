#include <stdlib.h>
#include <stdbool.h>

//F13
//J27
//M37
//M38
//M39

typedef struct tree tree_t; 
typedef struct node node_t; 

struct tree {
	node_t *root; 
}; 

struct node {
	int value; 
	node_t *left; 
	node_t *right; 
}; 

tree_t *tree_create() {
	tree_t *t = calloc(1, sizeof(struct tree)); 
	//t->root = NULL behövs ej pga calloc
	return t;
}

void node_destroy(node_t *n) {
	if (n == NULL) {
		return; 
	}

	node_destroy(n->left); 
	node_destroy(n->right); 
	free(n); 
}

//Riv ner ett träd	
void tree_destroy(tree_t *t) {
	node_destroy(t->root); 
	free(t); 	
}

//Leta efter ett element
bool tree_contains(tree_t *t, int value) {
	node_t *cursor = t->root; 

	while (cursor != NULL) {
		if (cursor->value == value) {
			return true; 
		} else if (value < cursor->value) {
			cursor =cursor->left;
		       //*cursur betyder att vi avrefererar cursor
		       //då ovan är samma som cursor = (*cursor).left	
		} else {
			cursor = cursor->right; 
		}	
	}
	return false; 
}

//Stoppa in ett element
//Ta bort element
