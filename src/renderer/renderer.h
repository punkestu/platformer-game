#ifndef RENDERER_H___
#define RENDERER_H___

#include <SDL2/SDL.h>
#include "../obj/obj.h"

void render(SDL_Renderer *renderer, struct Object *obj);
void render_objs(SDL_Renderer *renderer, struct List *listObj);

void move_camera(struct List *listObj, struct Vec2f *camera);
void follow_camera(struct Vec2f *camera, struct Movable *player);

#endif // RENDERER_H___