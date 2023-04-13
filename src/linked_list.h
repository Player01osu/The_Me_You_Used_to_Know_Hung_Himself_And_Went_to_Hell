#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct LinkedList {
	void *key;
	void *value;
	struct LinkedList *next;
} LinkedList;

void linked_list_push_front(LinkedList *root, void *key, void *value);

void linked_list_push(LinkedList *linked_list, void *key, void *value);

LinkedList *linked_list_new(void);

void linked_list_push(LinkedList *linked_list, void *key, void *value);

#endif // !LINKEDLIST
