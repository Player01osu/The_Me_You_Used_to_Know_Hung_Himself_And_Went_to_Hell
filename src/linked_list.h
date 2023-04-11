#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct LinkedList {
	char *key;
	char *value;
	struct LinkedList *next;
} LinkedList;

void linked_list_push_front(LinkedList *root, char *key, char *value);

void linked_list_push(LinkedList *linked_list, char *key, char *value);

LinkedList *linked_list_new(void);

void linked_list_push(LinkedList *linked_list, char *key, char *value);

#endif // !LINKEDLIST
