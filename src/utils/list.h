#ifndef LIST_H___
#define LIST_H___

#include "../include.h"

struct List
{
    void **items;
    size_t capacity;
    size_t size;
};

struct List* create_list();
struct List* create_list_with_capacity(size_t capacity);
struct List* create_list_with_items(void **items, size_t size);
void destroy_list(struct List *list);
void* get(struct List *list, size_t index);
void add(struct List *list, void *item);
void remove_at(struct List *list, size_t index);

#endif // LIST_H___