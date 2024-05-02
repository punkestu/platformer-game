#ifndef FACTORY_H__
#define FACTORY_H__

#include "../utils/list.h"
#include "../obj/obj.h"

struct Mob
{
    struct Object *obj;
    struct Movable *mov;
    struct SolidMovable *solidMov;
    struct Solid *solid;
    size_t index;
};
struct Factory
{
    struct List *list;
    struct List *obj;
    struct List *movable;
    struct List *solid;
    struct List *solidMovable;
};
struct Factory *create_list_mob();
struct Mob *create_mob(struct Factory *factory, SDL_Rect body);
void be_movable(struct Factory *factory, struct Mob *mob);
void be_solid(struct Factory *factory, struct Mob *mob, const char dir);
void be_solid_movable(struct Factory *factory, struct Mob *mob);
void delete_mob(struct Factory *factory, struct Mob *mob);
void destroy_list_mob(struct Factory *factory);

#endif // FACTORY_H__