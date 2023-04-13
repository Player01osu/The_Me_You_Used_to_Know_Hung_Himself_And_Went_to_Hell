#include <stdlib.h>
#include "linked_list.h"

LinkedList *linked_list_new(void)
{
	LinkedList *this = malloc(sizeof(LinkedList));
	this->value = NULL;
	this->key = NULL;
	this->next = NULL;

	return this;
}

void linked_list_push_front(LinkedList *root, void *key, void *value)
{
	LinkedList *new_node = malloc(sizeof(LinkedList));
	new_node->next = root->next;
	new_node->key = key;
	new_node->value = value;
	root->next = new_node;
}

void linked_list_push(LinkedList *linked_list, void *key, void *value)
{
	LinkedList *p = linked_list;

	while (p->next) {
		p = p->next;
	}
	p->next = malloc(sizeof(LinkedList));
	p = p->next;

	p->next = NULL;
	p->key = key;
	p->value = value;
}
