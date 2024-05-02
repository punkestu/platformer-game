#include "factory.h"

struct Factory *create_list_mob()
{
    struct Factory *mobList = malloc(sizeof(struct Factory));
    mobList->list = create_list();
    mobList->obj = create_list();
    mobList->movable = create_list();
    mobList->solid = create_list();
    mobList->solidMovable = create_list();
    return mobList;
}
struct Mob *create_mob(struct Factory *factory, SDL_Rect body)
{
    struct Mob *mob = malloc(sizeof(struct Mob));
    mob->obj = create_object(body);
    mob->mov = NULL;
    mob->solidMov = NULL;
    mob->solid = NULL;
    mob->index = factory->list->size;
    add(factory->list, mob);
    add(factory->obj, mob->obj);
    return mob;
}
void be_movable(struct Factory *factory, struct Mob *mob)
{
    mob->mov = create_movable(mob->obj);
    destroy_list(factory->movable);
    factory->movable = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->mov != NULL)
            add(factory->movable, mob->mov);
    }
}
void be_solid(struct Factory *factory, struct Mob *mob, const char dir)
{
    mob->solid = create_solid(&mob->obj->physic, dir);
    destroy_list(factory->solid);
    factory->solid = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->solid != NULL)
            add(factory->solid, mob->solid);
    }
}
void be_solid_movable(struct Factory *factory, struct Mob *mob)
{
    mob->solidMov = create_solid_movable(mob->mov);
    destroy_list(factory->solidMovable);
    factory->solidMovable = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->solidMov != NULL)
            add(factory->solidMovable, mob->solidMov);
    }
}
void delete_mob(struct Factory *factory, struct Mob *mob)
{
    remove_at(factory->list, mob->index);
    destroy_object(mob->obj);
    destroy_movable(mob->mov);
    destroy_solid_movable(mob->solidMov);
    destroy_solid(mob->solid);
    free(mob);
    destroy_list(factory->movable);
    factory->movable = create_list();
    destroy_list(factory->solid);
    factory->solid = create_list();
    destroy_list(factory->solidMovable);
    factory->solidMovable = create_list();
    destroy_list(factory->obj);
    factory->obj = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        mob->index = i;
        add(factory->obj, mob->obj);
        if (mob->mov != NULL)
            add(factory->movable, mob->mov);
        if (mob->solid != NULL)
            add(factory->solid, mob->solid);
        if (mob->solidMov != NULL)
            add(factory->solidMovable, mob->solidMov);
    }
}
void destroy_list_mob(struct Factory *factory)
{
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)factory->list->items[i];
        delete_mob(factory, mob);
    }
    destroy_list(factory->list);
    destroy_list(factory->movable);
    destroy_list(factory->solid);
    destroy_list(factory->solidMovable);
    free(factory);
}