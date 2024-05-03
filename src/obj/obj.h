#ifndef OBJ_H___
#define OBJ_H___

#include <SDL2/SDL.h>
#include "../utils/list.h"

enum Direction
{
    UP = 0b0001,
    DOWN = 0b0010,
    LEFT = 0b0100,
    RIGHT = 0b1000,
};

struct Vec2f
{
    float x;
    float y;
};

struct Object
{
    struct Vec2f pos;
};
struct Object *create_object(struct Vec2f pos);
void destroy_object(struct Object *obj);
SDL_bool is_colliding(struct Object *a, struct Object *b);

struct Renderable
{
    struct Object *body;
    SDL_Rect representation;
};
struct Renderable *create_renderable(struct Object *obj, const SDL_Rect representation);
void destroy_renderable(struct Renderable *rend);

struct Movable
{
    struct Object *body;
    struct Vec2f vel;
};
struct Movable *create_movable(struct Object *obj);
void destroy_movable(struct Movable *mov);
void move_movable(struct Movable *mov, int delta);
void move_with_gravity(struct Movable *mov, const float gravity, int delta);

int move_dir(SDL_bool isMoveLeft, SDL_bool isMoveRight);

struct Solid
{
    struct Object *body;
    SDL_Rect collBox;
    char dir;
};
struct Solid *create_solid(struct Object *body, const SDL_Rect collBox, const char dir);
void destroy_solid(struct Solid *solid);

struct SolidMovable
{
    struct Movable *mov;
    SDL_Rect collBox;
    char isColliding;
};
struct SolidMovable *create_solid_movable(struct Movable *mov, const SDL_Rect collBox);
void destroy_solid_movable(struct SolidMovable *solidMov);

void block_with_solid(struct SolidMovable *a, struct Solid *b, int delta);
void block_with_solids(struct List *listSolidMovable, struct List *listSolid, int delta);
void block_with_solid_movable(struct SolidMovable *a, struct SolidMovable *b, int delta);
void block_with_solid_movables(struct List *listSolidMovable, int delta);

#endif // OBJ_H___