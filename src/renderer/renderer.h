#ifndef RENDERER_H___
#define RENDERER_H___

#include "../include.h"
#include "../obj/obj.h"

void render(SDL_Renderer *renderer, struct Renderable *rend);
void render_objs(SDL_Renderer *renderer, struct List *listRenderable);

void render_gl(struct RenderableGL *rend);
void render_objs_gl(struct List *listRenderableGL);

void move_camera(struct List *listObj, struct Vec2f *camera);
void follow_camera(struct Vec2f *camera, struct Movable *player);

#endif // RENDERER_H___