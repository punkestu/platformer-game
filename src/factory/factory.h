#ifndef FACTORY_H__
#define FACTORY_H__

#include "../utils/list.h"
#include "../obj/obj.h"

struct Factory
{
    struct List *list;
    struct List *obj;
    struct List *renderable;
    struct List *movable;
    struct List *solid;
    struct List *solidMovable;
};
struct Factory *create_factory();
void clean_factory(struct Factory *factory);
void destroy_factory(struct Factory *factory);

struct Mob
{
    struct Object *obj;
    struct Renderable *rend;
    struct Movable *mov;
    struct SolidMovable *solidMov;
    struct Solid *solid;
    size_t index;
};
struct Mob *create_mob(struct Factory *factory, const struct Vec2f pos);
void be_renderable(struct Factory *factory, struct Mob *mob, const SDL_Rect representation);
void be_movable(struct Factory *factory, struct Mob *mob);
void be_solid(struct Factory *factory, struct Mob *mob, const SDL_Rect collBox, const char dir);
void be_solid_movable(struct Factory *factory, struct Mob *mob, const SDL_Rect collBox);
void delete_mob(struct Factory *factory, struct Mob *mob);

#endif // FACTORY_H__