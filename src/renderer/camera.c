#include "../obj/obj.h"

void move_camera(struct List *listObj, struct Vec2f *camera)
{
    for (int i = 0; i < listObj->size; i++)
    {
        struct Object *obj = (struct Object *)get(listObj, i);
        // obj->representation.x = obj->physic.x - camera->x;
        // obj->representation.y = obj->physic.y - camera->y;
    }
}
void follow_camera(struct Vec2f *camera, struct Movable *player)
{
    // camera->x = player->pos.x - 400;
    // camera->y = player->pos.y - 300;
}