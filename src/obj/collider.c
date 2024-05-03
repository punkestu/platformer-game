#include "obj.h"

// SDL_bool is_colliding(struct Object *a, struct Object *b){
//     return SDL_HasIntersection(&a->physic, &b->physic);
// }

void block_with_solid(struct SolidMovable *a, struct Solid *b, int delta)
{
    const float Ax = a->mov->body->pos.x + a->collBox.x;
    const float Axw = Ax + a->collBox.w;
    const float Ay = a->mov->body->pos.y + a->collBox.y;
    const float Ayh = Ay + a->collBox.h;
    const float Bx = b->body->pos.x + b->collBox.x;
    const float Bxw = Bx + b->collBox.w;
    const float By = b->body->pos.y + b->collBox.y;
    const float Byh = By + b->collBox.h;
    const float nextAx = Ax + a->mov->vel.x * (float)delta / 1000.f;
    const float nextAxw = nextAx + a->collBox.w;
    const float nextAy = Ay + a->mov->vel.y * (float)delta / 1000.f;
    const float nextAyh = nextAy + a->collBox.h;
    if (b->dir & UP && a->mov->vel.y > 0 && (nextAyh >= By && Ayh <= By && Ax <= Bxw && Axw >= Bx))
    {
        a->mov->body->pos.y = By - a->collBox.y - a->collBox.h;
        a->mov->vel.y = 0;
        a->isColliding |= DOWN;
    }
    if (b->dir & DOWN && a->mov->vel.y < 0 && (nextAy <= Byh && Ay >= Byh && Ax < Bxw && Axw > Bx))
    {
        a->mov->body->pos.y = Byh - a->collBox.y;
        a->mov->vel.y = 0;
        a->isColliding |= UP;
    }
    if (b->dir & LEFT && a->mov->vel.x > 0 && (nextAxw >= Bx && Axw <= Bx && Ay <= Byh && Ayh >= By))
    {
        a->mov->body->pos.x = Bx - a->collBox.x - a->collBox.w;
        a->mov->vel.x = 0;
        a->isColliding |= RIGHT;
    }
    if (b->dir & RIGHT && a->mov->vel.x < 0 && (nextAx <= Bxw && Ax >= Bxw && Ay < Byh && Ayh > By))
    {
        a->mov->body->pos.x = Bxw - a->collBox.x;
        a->mov->vel.x = 0;
        a->isColliding |= LEFT;
    }
}
void block_with_solids(struct List *listSolidMovable, struct List *listSolid, int delta)
{
    for (size_t i = 0; i < listSolidMovable->size; i++)
    {
        struct SolidMovable *movable = (struct SolidMovable *)get(listSolidMovable, i);
        for (size_t j = 0; j < listSolid->size; j++)
        {
            struct Solid *collider = (struct Solid *)get(listSolid, j);
            block_with_solid(movable, collider, delta);
        }
    }
}
void block_with_solid_movable(struct SolidMovable *a, struct SolidMovable *b, int delta)
{
    const float Ax = a->mov->body->pos.x + a->collBox.x;
    const float Axw = Ax + a->collBox.w;
    const float Ay = a->mov->body->pos.y + a->collBox.y;
    const float Ayh = Ay + a->collBox.h;
    const float Bx = b->mov->body->pos.x + b->collBox.x;
    const float Bxw = Bx + b->collBox.w;
    const float By = b->mov->body->pos.y + b->collBox.y;
    const float Byh = By + b->collBox.h;
    const float nextAx = Ax + a->mov->vel.x * (float)delta / 1000.f;
    const float nextAxw = nextAx + a->collBox.w;
    const float nextAy = Ay + a->mov->vel.y * (float)delta / 1000.f;
    const float nextAyh = nextAy + a->collBox.h;
    const float nextBx = Bx + b->mov->vel.x * (float)delta / 1000.f;
    const float nextBxw = nextBx + b->collBox.w;
    const float nextBy = By + b->mov->vel.y * (float)delta / 1000.f;
    const float nextByh = nextBy + b->collBox.h;
    if (a->mov->vel.y >= 0 && ((nextAyh >= nextBy || nextAyh >= By) && Ayh <= By && Ax <= Bxw && Axw >= Bx) && !(a->isColliding & DOWN))
    {
        a->mov->body->pos.y = By - a->collBox.y - a->collBox.h;
        a->mov->vel.y = 0;
        a->isColliding |= DOWN;
        if (b->mov->vel.y < 0 && !(b->isColliding & UP))
        {
            b->mov->vel.y = 0;
            b->isColliding |= UP;
        }
    }
    if (a->mov->vel.y <= 0 && ((nextAy <= nextByh || nextAy <= Byh) && Ay >= Byh && Ax <= Bxw && Axw >= Bx) && !(a->isColliding & UP))
    {
        a->mov->body->pos.y = Byh - a->collBox.y;
        a->mov->vel.y = 0;
        a->isColliding |= UP;
        if (b->mov->vel.y > 0 && !(b->isColliding & DOWN))
        {
            b->mov->vel.y = 0;
            b->isColliding |= DOWN;
        }
    }
    if (a->mov->vel.x >= 0 && ((nextAxw >= nextBx || nextAxw >= Bx) && Axw <= Bx && Ay < Byh && Ayh > By) && !(a->isColliding & RIGHT))
    {
        a->mov->body->pos.x = Bx - a->collBox.x - a->collBox.w;
        a->mov->vel.x = 0;
        a->isColliding |= RIGHT;
        if (b->mov->vel.x < 0 && !(b->isColliding & LEFT))
        {
            b->mov->vel.x = 0;
            b->isColliding |= LEFT;
        }
    }
    if (a->mov->vel.x <= 0 && ((nextAx <= nextBxw || nextAx <= Bxw) && Ax >= Bxw && Ay < Byh && Ayh > By) && !(a->isColliding & LEFT))
    {
        a->mov->body->pos.x = Bxw - a->collBox.x;
        a->mov->vel.x = 0;
        a->isColliding |= LEFT;
        if (b->mov->vel.x > 0 && !(b->isColliding & RIGHT))
        {
            b->mov->vel.x = 0;
            b->isColliding |= RIGHT;
        }
    }
}
void block_with_solid_movables(struct List *listSolidMovable, int delta)
{
    for (size_t i = 0; i < listSolidMovable->size; i++)
    {
        struct SolidMovable *movable = (struct SolidMovable *)get(listSolidMovable, i);
        movable->isColliding = 0;
    }
    for (size_t i = 0; i < listSolidMovable->size; i++)
    {
        struct SolidMovable *movable = (struct SolidMovable *)get(listSolidMovable, i);
        for (size_t j = 0; j < listSolidMovable->size; j++)
        {
            if (i == j)
                continue;
            struct SolidMovable *collider = (struct SolidMovable *)get(listSolidMovable, j);
            block_with_solid_movable(movable, collider, delta);
        }
    }
}
// void block_with_solid(struct Movable *a, SDL_Rect *b, const char dir, int delta)
// {
//     if (dir & UP && a->vel.y > 0 && (a->pos.y + a->body->h + a->vel.y * (float)delta / 1000.f >= b->y && a->pos.y + a->body->h <= b->y && a->pos.x <= b->x + b->w && a->pos.x + a->body->w >= b->x))
//     {
//         a->pos.y = b->y - a->body->h;
//         a->vel.y = 0;
//     }
//     if (dir & DOWN && a->vel.y < 0 && (a->pos.y + a->vel.y * (float)delta / 1000.f <= b->y + b->h && a->pos.y >= b->y + b->h && a->pos.x < b->x + b->w && a->pos.x + a->body->w > b->x))
//     {
//         a->pos.y = b->y + b->h;
//         a->vel.y = 0;
//     }
//     if (dir & LEFT && a->vel.x > 0 && (a->pos.x + a->body->w + a->vel.x * (float)delta / 1000.f >= b->x && a->pos.x + a->body->w <= b->x && a->pos.y < b->y + b->h && a->pos.y + a->body->h > b->y))
//     {
//         a->pos.x = b->x - a->body->w;
//         a->vel.x = 0;
//     }
//     if (dir & RIGHT && a->vel.x < 0 && (a->pos.x + a->vel.x * (float)delta / 1000.f <= b->x + b->w && a->pos.x >= b->x + b->w && a->pos.y < b->y + b->h && a->pos.y + a->body->h > b->y))
//     {
//         a->pos.x = b->x + b->w;
//         a->vel.x = 0;
//     }
//     if (a->pos.y + a->body->h == b->y && a->pos.x < b->x + b->w && a->pos.x + a->body->w > b->x)
//     {
//         a->isGrounded = SDL_TRUE;
//     }
// }
// void block_with_solids(struct List *listMovable, struct List *listSolid, int delta)
// {
//     for (size_t i = 0; i < listMovable->size; i++)
//     {
//         struct Movable *movable = (struct Movable *)get(listMovable, i);
//         for (size_t j = 0; j < listSolid->size; j++)
//         {
//             struct Solid *collider = (struct Solid *)get(listSolid, j);
//             block_with_solid(movable, collider->body, collider->dir, delta);
//         }
//     }
// }

// void block_with_solid_movable(struct SolidMovable *a, struct SolidMovable *b, int delta)
// {
//     const float nextAx = a->mov->pos.x + a->mov->vel.x * (float)delta / 1000.f;
//     const float nextAxw = nextAx + a->mov->body->w;
//     const float nextAy = a->mov->pos.y + a->mov->vel.y * (float)delta / 1000.f;
//     const float nextAyh = nextAy + a->mov->body->h;
//     const float nextBx = b->mov->pos.x + b->mov->vel.x * (float)delta / 1000.f;
//     const float nextBxw = nextBx + b->mov->body->w;
//     const float nextBy = b->mov->pos.y + b->mov->vel.y * (float)delta / 1000.f;
//     const float nextByh = nextBy + b->mov->body->h;
//     if (a->mov->vel.y >= 0 && ((nextAyh >= nextBy || nextAyh >= b->mov->pos.y) && a->mov->pos.y + a->mov->body->h <= b->mov->pos.y && a->mov->pos.x <= b->mov->pos.x + b->mov->body->w && a->mov->pos.x + a->mov->body->w >= b->mov->body->x) && !(a->isColliding & DOWN))
//     {
//         a->mov->pos.y = b->mov->pos.y - a->mov->body->h;
//         a->mov->vel.y = 0;
//         a->isColliding |= DOWN;
//         if (b->mov->vel.y < 0 && !(b->isColliding & UP))
//         {
//             b->mov->vel.y = 0;
//             b->isColliding |= UP;
//         }
//     }
//     if (a->mov->vel.y <= 0 && ((nextAy <= nextByh || nextAy <= b->mov->pos.y + b->mov->body->h) && a->mov->pos.y >= b->mov->pos.y + b->mov->body->h && a->mov->pos.x <= b->mov->pos.x + b->mov->body->w && a->mov->pos.x + a->mov->body->w >= b->mov->pos.x) && !(a->isColliding & UP))
//     {
//         a->mov->pos.y = b->mov->pos.y + b->mov->body->h;
//         a->mov->vel.y = 0;
//         a->isColliding |= UP;
//         if (b->mov->vel.y > 0 && !(b->isColliding & DOWN))
//         {
//             b->mov->vel.y = 0;
//             b->isColliding |= DOWN;
//         }
//     }
//     if (a->mov->vel.x >= 0 && ((nextAxw >= nextBx || nextAxw >= b->mov->pos.x) && a->mov->pos.x + a->mov->body->w <= b->mov->pos.x && a->mov->pos.y < b->mov->pos.y + b->mov->body->h && a->mov->pos.y + a->mov->body->h > b->mov->body->y) && !(a->isColliding & RIGHT))
//     {
//         a->mov->pos.x = b->mov->pos.x - a->mov->body->w;
//         a->mov->vel.x = 0;
//         a->isColliding |= RIGHT;
//         if (b->mov->vel.x < 0 && !(b->isColliding & LEFT))
//         {
//             b->mov->vel.x = 0;
//             b->isColliding |= LEFT;
//         }
//     }
//     if (a->mov->vel.x <= 0 && ((nextAx <= nextBxw || nextAx <= b->mov->pos.x + b->mov->body->w) && a->mov->pos.x >= b->mov->pos.x + b->mov->body->w && a->mov->pos.y < b->mov->pos.y + b->mov->body->h && a->mov->pos.y + a->mov->body->h > b->mov->pos.y) && !(a->isColliding & LEFT))
//     {
//         a->mov->pos.x = b->mov->pos.x + b->mov->body->w;
//         a->mov->vel.x = 0;
//         a->isColliding |= LEFT;
//         if (b->mov->vel.x > 0 && !(b->isColliding & RIGHT))
//         {
//             b->mov->vel.x = 0;
//             b->isColliding |= RIGHT;
//         }
//     }
//     if (a->mov->pos.y + a->mov->body->h == b->mov->body->y && a->mov->pos.x < b->mov->pos.x + b->mov->body->w && a->mov->pos.x + a->mov->body->w > b->mov->pos.x)
//     {
//         a->mov->isGrounded = SDL_TRUE;
//     }
// }
// void block_with_solid_movables(struct List *listSolidMovable, int delta)
// {
//     for (size_t i = 0; i < listSolidMovable->size; i++)
//     {
//         struct SolidMovable *movable = (struct SolidMovable *)get(listSolidMovable, i);
//         movable->isColliding = 0;
//     }
//     for (size_t i = 0; i < listSolidMovable->size; i++)
//     {
//         struct SolidMovable *movable = (struct SolidMovable *)get(listSolidMovable, i);
//         for (size_t j = 0; j < listSolidMovable->size; j++)
//         {
//             if (i == j)
//                 continue;
//             struct SolidMovable *collider = (struct SolidMovable *)get(listSolidMovable, j);
//             block_with_solid_movable(movable, collider, delta);
//         }
//     }
// }