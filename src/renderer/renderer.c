#include "renderer.h"
#include <SDL2/SDL.h>

void render(SDL_Renderer *renderer, struct Renderable *rend)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect buffer = {rend->body->pos.x + rend->representation.x, rend->body->pos.y + rend->representation.y, rend->representation.w, rend->representation.h};
    SDL_RenderDrawRect(renderer, &buffer);
}
void render_objs(SDL_Renderer *renderer, struct List *listRenderable)
{
    for (int i = 0; i < listRenderable->size; i++)
    {
        struct Renderable *rend = (struct Renderable *)get(listRenderable, i);
        render(renderer, rend);
    }
}

void render_gl(struct RenderableGL *rend)
{
    glUseProgram(rend->shaderID);
    glBindVertexArray(rend->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void render_objs_gl(struct List *listRenderableGL)
{
    for (int i = 0; i < listRenderableGL->size; i++)
    {
        struct RenderableGL *rend = (struct RenderableGL *)get(listRenderableGL, i);
        render_gl(rend);
    }
}