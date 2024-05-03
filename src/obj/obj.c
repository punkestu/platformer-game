#include "obj.h"
struct Object *create_object(struct Vec2f pos)
{
    struct Object *obj = malloc(sizeof(struct Object));
    obj->pos = pos;
    return obj;
}
void destroy_object(struct Object *obj)
{
    free(obj);
}

struct Renderable *create_renderable(struct Object *obj, const SDL_Rect representation)
{
    struct Renderable *rend = malloc(sizeof(struct Renderable));
    rend->body = obj;
    rend->representation = representation;
    return rend;
}
void destroy_renderable(struct Renderable *rend)
{
    free(rend);
}

struct Movable *create_movable(struct Object *obj)
{
    struct Movable *mov = malloc(sizeof(struct Movable));
    mov->body = obj;
    mov->vel = (struct Vec2f){0, 0};
    return mov;
}
void destroy_movable(struct Movable *mov)
{
    free(mov);
}
void move_movable(struct Movable *mov, int delta)
{
    mov->body->pos.x += mov->vel.x * (float)delta / 1000.f;
    mov->body->pos.y += mov->vel.y * (float)delta / 1000.f;
}
void move_with_gravity(struct Movable *mov, const float gravity, int delta)
{
    mov->vel.y += gravity;
}
int move_dir(SDL_bool isMoveLeft, SDL_bool isMoveRight)
{
    return (isMoveLeft ? -1 : (isMoveRight ? 1 : 0));
}

struct Solid *create_solid(struct Object *body, const SDL_Rect collBox, const char dir)
{
    struct Solid *solid = malloc(sizeof(struct Solid));
    solid->body = body;
    solid->collBox = collBox;
    solid->dir = dir;
    return solid;
}
void destroy_solid(struct Solid *solid)
{
    free(solid);
}

struct SolidMovable *create_solid_movable(struct Movable *mov, const SDL_Rect collBox)
{
    struct SolidMovable *solidMov = malloc(sizeof(struct SolidMovable));
    solidMov->mov = mov;
    solidMov->collBox = collBox;
    return solidMov;
}
void destroy_solid_movable(struct SolidMovable *solidMov)
{
    free(solidMov);
}