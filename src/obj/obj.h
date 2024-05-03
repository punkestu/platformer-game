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
    SDL_Rect physic;
    SDL_Rect representation;
};
struct Object *create_object(SDL_Rect body);
void destroy_object(struct Object *obj);
SDL_bool is_colliding(struct Object *a, struct Object *b);

struct Movable
{
    SDL_Rect *body;
    struct Vec2f pos;
    struct Vec2f vel;
    SDL_bool isGrounded;
};
struct Movable *create_movable(struct Object *obj);
void destroy_movable(struct Movable *mov);
void move_movable(struct Movable *mov, int delta);
int move_dir(SDL_bool isMoveLeft, SDL_bool isMoveRight);
void move_with_gravity(struct Movable *mov, const float gravity, int delta);

struct Solid
{
    SDL_Rect *body;
    char dir;
};
struct Solid *create_solid(SDL_Rect *body, const char dir);
void destroy_solid(struct Solid *solid);
void block_with_solid(struct Movable *a, SDL_Rect *b, const char dir, int delta);
void block_with_solids(struct List *listMovable, struct List *listSolid, int delta);

struct SolidMovable
{
    struct Movable *mov;
    char isColliding;
};
struct SolidMovable *create_solid_movable(struct Movable *mov);
void destroy_solid_movable(struct SolidMovable *solidMov);
void block_with_solid_movable(struct SolidMovable *a, struct SolidMovable *b, int delta);
void block_with_solid_movables(struct List *listSolidMovable, int delta);

#endif // OBJ_H___