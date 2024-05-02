#include "obj.h"
struct Object *create_object(SDL_Rect body)
{
    struct Object *obj = malloc(sizeof(struct Object));
    obj->physic = body;
    obj->representation = body;
    return obj;
}
void destroy_object(struct Object* obj)
{
    free(obj);
}

struct Movable *create_movable(struct Object *obj)
{
    struct Movable *mov = malloc(sizeof(struct Movable));
    mov->body = &obj->physic;
    mov->pos = (struct Vec2f){obj->physic.x, obj->physic.y};
    mov->vel = (struct Vec2f){0, 0};
    mov->isGrounded = SDL_FALSE;
    return mov;
}
void destroy_movable(struct Movable* mov)
{
    free(mov);
}
void move_movable(struct Movable *mov, int delta)
{
    mov->pos.x += mov->vel.x * (float)delta / 1000.f;
    mov->pos.y += mov->vel.y * (float)delta / 1000.f;
    mov->body->x = mov->pos.x;
    mov->body->y = mov->pos.y;
}
int move_dir(SDL_bool isMoveLeft, SDL_bool isMoveRight)
{
    return (isMoveLeft ? -1 : (isMoveRight ? 1 : 0));
}
void move_with_gravity(struct Movable *mov, const float gravity, int delta)
{
    mov->vel.y += gravity;
}

struct Solid* create_solid(SDL_Rect *body, const char dir)
{
    struct Solid *solid = malloc(sizeof(struct Solid));
    solid->body = body;
    solid->dir = dir;
    return solid;
}
void destroy_solid(struct Solid* solid)
{
    free(solid);
}

struct SolidMovable* create_solid_movable(struct Movable *mov)
{
    struct SolidMovable *solidMov = malloc(sizeof(struct SolidMovable));
    solidMov->mov = mov;
    return solidMov;
}
void destroy_solid_movable(struct SolidMovable* solidMov)
{
    free(solidMov);
}