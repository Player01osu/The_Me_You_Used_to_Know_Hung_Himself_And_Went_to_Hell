#include <stdlib.h>

typedef struct LinkedList {
	char *key;
	char *value;
	struct LinkedList *next;
} LinkedList;

void linked_list_push(LinkedList *linked_list, char *key, char *value);

LinkedList *linked_list_new(void)
{
	LinkedList *this = malloc(sizeof(LinkedList));
	this->value = NULL;
	this->key = NULL;
	this->next = NULL;

	return this;
}

void linked_list_push_front(LinkedList *root, char *key, char *value)
{
	LinkedList *new_node = malloc(sizeof(LinkedList));
	new_node->next = root->next;
	root->next = new_node;
}

void linked_list_push(LinkedList *linked_list, char *key, char *value)
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
