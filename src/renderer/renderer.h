#ifndef RENDERER_H___
#define RENDERER_H___

#include <SDL2/SDL.h>
#include "../obj/obj.h"

void render(SDL_Renderer *renderer, struct Object *obj);
void render_objs(SDL_Renderer *renderer, struct List *listObj);

#endif // RENDERER_H___