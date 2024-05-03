#include "factory.h"

struct Factory *create_factory()
{
    struct Factory *mobList = malloc(sizeof(struct Factory));
    mobList->list = create_list();
    mobList->obj = create_list();
    mobList->renderable = create_list();
    mobList->renderableGL = create_list();
    mobList->movable = create_list();
    mobList->solid = create_list();
    mobList->solidMovable = create_list();
    return mobList;
}
void clean_factory(struct Factory *factory)
{
    destroy_list(factory->list);
    factory->list = create_list();
    destroy_list(factory->obj);
    factory->obj = create_list();
    destroy_list(factory->renderable);
    factory->renderable = create_list();
    destroy_list(factory->renderableGL);
    factory->renderableGL = create_list();
    destroy_list(factory->movable);
    factory->movable = create_list();
    destroy_list(factory->solid);
    factory->solid = create_list();
    destroy_list(factory->solidMovable);
    factory->solidMovable = create_list();
}
void destroy_factory(struct Factory *factory)
{
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)factory->list->items[i];
        delete_mob(factory, mob);
    }
    destroy_list(factory->list);
    destroy_list(factory->obj);
    destroy_list(factory->renderable);
    destroy_list(factory->renderableGL);
    destroy_list(factory->movable);
    destroy_list(factory->solid);
    destroy_list(factory->solidMovable);
    free(factory);
}

struct Mob *create_mob(struct Factory *factory, const struct Vec2f pos)
{
    struct Mob *mob = malloc(sizeof(struct Mob));
    mob->obj = create_object(pos);
    mob->rend = NULL;
    mob->rendGL = NULL;
    mob->mov = NULL;
    mob->solidMov = NULL;
    mob->solid = NULL;
    mob->index = factory->list->size;
    add(factory->list, mob);
    add(factory->obj, mob->obj);
    return mob;
}
void be_renderable(struct Factory *factory, struct Mob *mob, const SDL_Rect representation)
{
    mob->rend = create_renderable(mob->obj, representation);
    destroy_list(factory->renderable);
    factory->renderable = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->rend != NULL)
            add(factory->renderable, mob->rend);
    }
}
void be_renderable_gl(struct Factory *factory, struct Mob *mob, const struct Vec4f boundary)
{
    mob->rendGL = create_renderable_gl(mob->obj, boundary);
    destroy_list(factory->renderableGL);
    factory->renderableGL = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->rendGL != NULL)
            add(factory->renderableGL, mob->rendGL);
    }
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
void be_solid(struct Factory *factory, struct Mob *mob, const SDL_Rect collBox, const char dir)
{
    mob->solid = create_solid(mob->obj, collBox, dir);
    destroy_list(factory->solid);
    factory->solid = create_list();
    for (size_t i = 0; i < factory->list->size; i++)
    {
        struct Mob *mob = (struct Mob *)get(factory->list, i);
        if (mob->solid != NULL)
            add(factory->solid, mob->solid);
    }
}
void be_solid_movable(struct Factory *factory, struct Mob *mob, const SDL_Rect collBox)
{
    mob->solidMov = create_solid_movable(mob->mov, collBox);
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
    destroy_renderable(mob->rend);
    destroy_renderable_gl(mob->rendGL);
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
        if (mob->rend != NULL)
            add(factory->renderable, mob->rend);
        if (mob->rendGL != NULL)
            add(factory->renderableGL, mob->rendGL);
        if (mob->mov != NULL)
            add(factory->movable, mob->mov);
        if (mob->solid != NULL)
            add(factory->solid, mob->solid);
        if (mob->solidMov != NULL)
            add(factory->solidMovable, mob->solidMov);
    }
}