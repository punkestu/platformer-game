#include "list.h"

struct List *create_list()
{
    struct List *list = malloc(sizeof(struct List));
    list->items = malloc(sizeof(void *));
    list->capacity = 1;
    list->size = 0;
    return list;
}
struct List *create_list_with_capacity(size_t capacity)
{
    struct List *list = malloc(sizeof(struct List));
    list->items = malloc(sizeof(void *) * capacity);
    list->capacity = capacity;
    list->size = 0;
    return list;
}
struct List *create_list_with_items(void **items, size_t size)
{
    struct List *list = malloc(sizeof(struct List));
    list->items = items;
    list->capacity = size;
    list->size = size;
    return list;
}
void destroy_list(struct List *list)
{
    if(list->items != NULL)
        free(list->items);
    free(list);
}
void *get(struct List *list, size_t index)
{
    return list->items[index];
}
void add(struct List *list, void *item)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(void *) * list->capacity);
    }
    list->items[list->size++] = item;
}
void remove_at(struct List *list, size_t index)
{
    for (size_t i = index; i < list->size - 1; i++)
    {
        list->items[i] = list->items[i + 1];
    }
    list->size--;
}